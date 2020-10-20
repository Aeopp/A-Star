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
D3DXMatrixIdentity(D3DXMATRIX *pOut); 항등행렬로 만들어주는 함수. 
항등행렬 - 행렬의 초기값이라 생각하면 편하다. 예를 들어 포인터는 nullptr로 초기화 하듯 행렬도 항등행렬로 초기화를 한다. 
항등행렬의 경우 행렬의 곱셈에서 교환법칙 성립된다. 
1	0	0	0
0	1	0	0
0	0	1	0
0	0	0	1
// 크기 관련 함수. 
D3DXMatrixScaling(D3DXMATRIX *pOut, FLOAT sx, FLOAT sy, FLOAT sz);
11, 22, 33번째 원소에 영향을 끼친다. 중요한건 크기 넣어주는것은 비율을 넣어줘야 한다. 
예를들어 2배 혹은 3배 요론식으로. 
*행렬 관련 함수들은 아웃풋으로 받은 행렬을 항등행렬로 만들고 연산을 수행한다. 
X	0	0	0
0	X	0	0
0	0	X	0
0	0	0	1

// 이동관련 행렬함수. 
D3DXMatrixTranslation( D3DXMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z )
*행렬 관련 함수들은 아웃풋으로 받은 행렬을 항등행렬로 만들고 연산을 수행한다.
1	0	0	0
0	1	0	0
0	0	1	0
X	X	X	1

//회전관련 행렬 함수 X,Y, Z
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

// 벡터와 행렬간의 곱셈에 사용되는 함수. 
D3DXVec3TransformCoord(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM);
D3DXVec3TransformNormal(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM);
*/

