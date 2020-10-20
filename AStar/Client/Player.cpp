#include "stdafx.h"
#include "Player.h"
#include "AStar_Manager.h"


CPlayer::CPlayer()
	:MoveSpeed(650.f)
{
}


CPlayer::~CPlayer()
{
}

void CPlayer::FrameMove(float fSpeed)
{
	m_tFrame.fStartFrame += m_tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;

	if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
	{
		m_tFrame.fStartFrame = 0.f; 
	}
}

HRESULT CPlayer::Ready_GameObject()
{
	m_tInfo.vPos = { float(WINCX >> 1), float(WINCY >> 1 ), 0.f };
	m_tInfo.vSize = { 1.f ,1.f, 0.f }; 
	m_tFrame = { 0.f, 6.f };
	
	return S_OK;
}

int CPlayer::Update_GameObject()
{
	MoveAStar();

	if (D3DXVec3Length(&(CurrentMoveTarget - m_tInfo.vPos)) < 30.f)
	{
		if (!Paths.empty())
		{
			CurrentMoveTarget = Paths.back();
			Paths.pop_back();
		}
	}

	if(D3DXVec3Length(&(CurrentMoveTarget - m_tInfo.vPos)) >= 30.f)
	{
		_vec3 Dir;
		D3DXVec3Normalize(&Dir, &(CurrentMoveTarget - m_tInfo.vPos)); 
		 m_tInfo.vPos += (Dir* MoveSpeed* CTime_Manager::Get_Instance()->Get_TimeDelta());
		
		 if (D3DXVec3Length(&(CurrentMoveTarget - m_tInfo.vPos)) < 10.f)
		 {
			 m_tInfo.vPos = CurrentMoveTarget;
		}
	}

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update_GameObject()
{
	FrameMove(1.f); 
}

void CPlayer::Render_GameObject()
{
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", L"Attack", DWORD(m_tFrame.fStartFrame));
	if (nullptr == pTexInfo)
		return;
	float fCenterX = pTexInfo->tImageInfo.Width >> 1; 
	float fCenterY = pTexInfo->tImageInfo.Height >> 1; 
	_matrix matScale, matRotZ, matTrans, matWorld, mRatio;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixScaling(&mRatio, 0.5f, 0.5f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X) , m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)-87, 0.f); 
	matWorld = matScale * matTrans*mRatio;
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld); 
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)); 
}

void CPlayer::Release_GameObject()
{
}

CPlayer * CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer; 
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance; 
		pInstance = nullptr; 
	}
	return pInstance;
}

void CPlayer::Free()
{

}

void CPlayer::MoveAStar()
{
	/*POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWND, &pt);
	m_tInfo.vPos = _vec3{ (float)pt.x, (float)pt.y,0.f };*/

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWND, &pt);
		_vec3 Goal = { (float)pt.x,(float)pt.y,0.f };
		Goal *= 2.f;
		Goal.x += CScroll_Manager::Get_Scroll().x;
		Goal.y += CScroll_Manager::Get_Scroll().y;
		Paths = CAStar_Manager::Get_Instance()->StartAStar(m_tInfo.vPos, Goal);
		CurrentMoveTarget =m_tInfo.vPos; 
	}
}

/*
D3DXMatrixIdentity(D3DXMATRIX *pOut); �׵���ķ� ������ִ� �Լ�. 
�׵���� - ����� �ʱⰪ�̶� �����ϸ� ���ϴ�. ���� ��� �����ʹ� nullptr�� �ʱ�ȭ �ϵ� ��ĵ� �׵���ķ� �ʱ�ȭ�� �Ѵ�. 
�׵������ ��� ����� �������� ��ȯ��Ģ �����ȴ�. 
1	0	0	0
0	1	0	0
0	0	1	0
0	0	0	1
// ũ�� ���� �Լ�. 
D3DXMatrixScaling(D3DXMATRIX *pOut, FLOAT sx, FLOAT sy, FLOAT sz);
11, 22, 33��° ���ҿ� ������ ��ģ��. �߿��Ѱ� ũ�� �־��ִ°��� ������ �־���� �Ѵ�. 
������� 2�� Ȥ�� 3�� ��н�����. 
*��� ���� �Լ����� �ƿ�ǲ���� ���� ����� �׵���ķ� ����� ������ �����Ѵ�. 
X	0	0	0
0	X	0	0
0	0	X	0
0	0	0	1

// �̵����� ����Լ�. 
D3DXMatrixTranslation( D3DXMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z )
*��� ���� �Լ����� �ƿ�ǲ���� ���� ����� �׵���ķ� ����� ������ �����Ѵ�.
1	0	0	0
0	1	0	0
0	0	1	0
X	X	X	1

//ȸ������ ��� �Լ� X,Y, Z
D3DXMatrixRotationX( D3DXMATRIX *pOut, FLOAT Angle )
1		0		0		0
0		cos		sin		0
0		-sin	cos		0
0		0		0		1	

D3DXMatrixRotationY(D3DXMATRIX *pOut, FLOAT Angle)
cos		0		-sin	0
0		1		0		0
sin		0		cos		0
0		0		0		1

D3DXMatrixRotationZ(D3DXMATRIX *pOut, FLOAT Angle)
cos		sin		0		0
-sin	cos		0		0
0		0		1		0
0		0		0		1

// ���Ϳ� ��İ��� ������ ���Ǵ� �Լ�. 
D3DXVec3TransformCoord(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM);
D3DXVec3TransformNormal(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM);
*/

