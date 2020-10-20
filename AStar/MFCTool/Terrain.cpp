#include "stdafx.h"
#include "Terrain.h"
#include "MFCToolView.h"


CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release(); 
}

void CTerrain::TileChange_Terrain(const _vec3 & vPos, const BYTE & byDrawID, const BYTE & byOption)
{
	int iIndex = Get_TileIndex(vPos); 

	if (-1 == iIndex)
		return; 

	m_vecTile[iIndex]->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = byOption; 
}

int CTerrain::Get_TileIndex(const _vec3 & vPos)
{
	for (size_t i = 0 ; i < m_vecTile.size(); ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}
	return -1;
}

bool CTerrain::IsPicking(const _vec3 & vPos, const int & iIndex)
{

// 	// y= ax + b ; 
// 	// 0 = ax + b - y; 
// 	// a 구하자.
// 	float fa[4] =
// 	{
// 		(TILECY * 0.5f) / (TILECX * 0.5f),
// 		-(TILECY * 0.5f) / (TILECX * 0.5f),
// 		(TILECY * 0.5f) / (TILECX * 0.5f),
// 		-(TILECY * 0.5f) / (TILECX * 0.5f)
// 	};
// 	_vec3 vPoint[4]= 
// 	{
// 		{m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y  + (TILECY * 0.5f), 0.f},
// 		{ m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y , 0.f },
// 		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f },
// 		{ m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y , 0.f }
// 	};
// 	// y= ax + b -> b = y - ax ; 
// 	float fB[4] = 
// 	{
// 		vPoint[0].y - fa[0] * vPoint[0].x,
// 		vPoint[1].y - fa[1] * vPoint[1].x,
// 		vPoint[2].y - fa[2] * vPoint[2].x,
// 		vPoint[3].y - fa[3] * vPoint[3].x
// 
// 	};
// 	// 1번째 줄에 이 포스를 대입해서 연산을 했을 경우 양수 
// 	if (0 < fa[0] * vPos.x + fB[0] - vPos.y &&
// 		0 < fa[1] * vPos.x + fB[1] - vPos.y &&
// 		0 > fa[2] * vPos.x + fB[2] - vPos.y &&
// 		0 > fa[3] * vPos.x + fB[3] - vPos.y )
// 		return true;

	//1. 마름모꼴의 정점을 4개 구하자! 
	_vec3 vPoint[4] =
	{
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f },
		{ m_vecTile[iIndex]->vPos.x + (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y , 0.f },
		{ m_vecTile[iIndex]->vPos.x, m_vecTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f },
		{ m_vecTile[iIndex]->vPos.x - (TILECX * 0.5f), m_vecTile[iIndex]->vPos.y , 0.f }
	};
	//2. 마름모꼴 방향벡터를 구하자!

	_vec3 vRhombusDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};
	//3. 방향벡터의 법선벡터를 구하자! 
	_vec3 vRhombusNormal[4] = 
	{
		{ -vRhombusDir[0].y, vRhombusDir[0].x, 0.f },
		{ -vRhombusDir[1].y, vRhombusDir[1].x, 0.f },
		{ -vRhombusDir[2].y, vRhombusDir[2].x, 0.f },
		{ -vRhombusDir[3].y, vRhombusDir[3].x, 0.f }
	};
	//4.마름모꼴 정점에서 마우스를 바라보는 방향벡터를 구해라!!! 
	_vec3 vMouseDir[4] =
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3],

	};
	// 내가 구한 마우스를 바라보는 방향벡터와 마름모꼴의 법선벡터를 내적하자! 
	for (int i = 0 ; i < 4; ++i)
	{
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]); 
		D3DXVec3Normalize(&vRhombusNormal[i], &vRhombusNormal[i]);

		if (0 < D3DXVec3Dot(&vRhombusNormal[i], &vMouseDir[i]))
			return false; 
	}
	return true; 
}

void CTerrain::Set_Ratio(_matrix & matWorld, float fRatioX, float fRatioY)
{
	matWorld._11 *= fRatioX;
	matWorld._21 *= fRatioX;
	matWorld._31 *= fRatioX;
	matWorld._41 *= fRatioX;

	matWorld._12 *= fRatioY;
	matWorld._22 *= fRatioY;
	matWorld._32 *= fRatioY;
	matWorld._42 *= fRatioY;


}

HRESULT CTerrain::Ready_Terrain()
{
	TILE* pTile = nullptr; 
	m_vecTile.reserve(TILEX * TILEY); 
	float fX = 0.f; 
	float fY = 0.f; 
	for (int i = 0 ; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			pTile = new TILE; 
			fX = float((j * TILECX) + (i % 2) * (TILECX >> 1));
			fY = float((TILECY >> 1) * i);
			pTile->vPos = { fX, fY, 0.f }; 
			pTile->vSize = { 1.f, 1.f, 0.f }; 
			pTile->iIndex = j + (i * TILEX);
			pTile->iParentIndex = 0; 
			pTile->byDrawID = 10;
			pTile->byOption = 0;
			m_vecTile.emplace_back(pTile);
		}
	}
	return S_OK;
}

void CTerrain::Render_Terrain()
{
	_matrix matScale, matTrans, matWrold; 
	
	TCHAR szBuf[MAX_PATH] = L""; 
	int iIndex = 0; 
	DWORD dwSize = m_vecTile.size();
	for (size_t i = 0 ; i < dwSize; ++i )
	{
		swprintf_s(szBuf, __T("%d"), iIndex);
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[i]->byDrawID); 
		assert(!(nullptr == pTexInfo));
// 		if (nullptr == pTexInfo)
// 			return; 
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1); 
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1); 
		SB_HORZ; SB_VERT;
		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f); 
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x - m_pView->GetScrollPos(0), m_vecTile[i]->vPos.y - m_pView->GetScrollPos(1), 0.f);
		matWrold = matScale * matTrans; 

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWrold);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)); 

		CGraphic_Device::Get_Instance()->Get_Font()->DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
		++iIndex; 
	}
// 	D3DXVECTOR2 vLinePos[2] = { {100.f, 100.f}, {200.f, 200.f} }; 
// 	CGraphic_Device::Get_Instance()->Get_Sprite()->End(); 
// 	CGraphic_Device::Get_Instance()->Get_Line()->SetWidth(100.f);
// 	CGraphic_Device::Get_Instance()->Get_Line()->Draw(vLinePos, 2, (D3DCOLOR_ARGB(255, 255, 0, 0)));
// 	CGraphic_Device::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
}

void CTerrain::Mini_Render_Terrain()
{
	_matrix matScale, matTrans, matWrold, matRatio;

	DWORD dwSize = m_vecTile.size();
	for (size_t i = 0; i < dwSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		assert(!(nullptr == pTexInfo));
		// 		if (nullptr == pTexInfo)
		// 			return; 
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);
		
		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
		D3DXMatrixScaling(&matRatio, 0.2f, 0.2f, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x - m_pView->GetScrollPos(0), m_vecTile[i]->vPos.y - m_pView->GetScrollPos(1), 0.f);
		matWrold = matScale * matTrans;
		matWrold *= matRatio; 
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWrold);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CTerrain::Release()
{
	for (auto& pTile : m_vecTile)
		Safe_Delete(pTile); 
	m_vecTile.clear(); 
	m_vecTile.shrink_to_fit(); 
}
