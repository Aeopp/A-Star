#include "stdafx.h"
#include "Terrain.h"
#include <array>
#include <sstream>
#include "AStar_Manager.h"


CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	Release_GameObject();
}

HRESULT CTerrain::LoadTerrain(const wstring & wstrFilePath)
{
	for (auto& pTile : m_vecTile)
		Safe_Delete(pTile);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();

	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwByte = 0;
	TILE* pTile = nullptr;
	while (true)
	{
		pTile = new TILE;
		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);
		if (0 == dwByte)
		{
			Safe_Delete(pTile);
			break;
		}
		m_vecTile.emplace_back(pTile);
	}
	return S_OK;
}

HRESULT CTerrain::Ready_GameObject()
{
	if (FAILED(LoadTerrain(L"../Data/TileData.dat")))
	{
		ERR_MSG(L"Load 1Stage Failed");
		return E_FAIL;
	}

	Create_Graph_Terrain();
	return S_OK;
}

int CTerrain::Update_GameObject()
{
	float fTimeDelta = CTime_Manager::Get_Instance()->Get_TimeDelta();
	float fSpeed = 1000.f * fTimeDelta;
	if (GetAsyncKeyState(VK_LEFT))
		CScroll_Manager::Set_Scroll({ -fSpeed, 0.f, 0.f });
	if (GetAsyncKeyState(VK_RIGHT))
		CScroll_Manager::Set_Scroll({ fSpeed, 0.f, 0.f });
	if (GetAsyncKeyState(VK_UP))
		CScroll_Manager::Set_Scroll({ 0.f,-fSpeed, 0.f });
	if (GetAsyncKeyState(VK_DOWN))
		CScroll_Manager::Set_Scroll({ 0.f,fSpeed, 0.f });
	return 0;
}

void CTerrain::Late_Update_GameObject()
{
}

void CTerrain::Render_GameObject()
{
	_matrix matScale, matTrans, matWrold, matRatio;

	DWORD dwSize = m_vecTile.size();

	auto& _Open = CAStar_Manager::Get_Instance()->_Open;
	auto& _Close = CAStar_Manager::Get_Instance()->_Close;

	int Start = CAStar_Manager::Get_Instance()->Start;
	int Goal = CAStar_Manager::Get_Instance()->Goal;

	std::wstringstream wss;
	for (size_t i = 0; i < dwSize; ++i)
	{
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_vecTile[i]->byDrawID);
		assert(!(nullptr == pTexInfo));
		// 		if (nullptr == pTexInfo)
		// 			return; 
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		D3DXMatrixScaling(&matScale, m_vecTile[i]->vSize.x, m_vecTile[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_vecTile[i]->vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_vecTile[i]->vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);
		D3DXMatrixScaling(&matRatio, 0.5f, 0.5f, 0.f);
		matWrold = matScale * matTrans*matRatio;
		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWrold);

		D3DCOLOR _Color = D3DCOLOR_ARGB(255, 255, 255, 255);

		if (   !_Open.empty() && _Open.find(i) != std::end(_Open))
		{
			_Color = D3DCOLOR_ARGB(255, 0, 255, 255);
		}

		if (  !_Close.empty() && _Close.find(i) != std::end(_Close))
		{
			_Color = D3DCOLOR_ARGB(255, 255, 0, 255);
		}

		if (Start != -1 && i==Start)
		{
			_Color = D3DCOLOR_ARGB(255, 0, 0, 125);
		}
		if (Goal != -1 && i==Goal)
		{
			_Color = D3DCOLOR_ARGB(255, 125, 125, 0);
		}

		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, _Color);
		
		/*for (size_t j = 0; j < m_vecGraph[i].size(); ++j)
		{
			auto iter=m_vecGraph[i].begin();
			std::advance(iter, j);
			wss << (*iter)->iIndex << (j==1) ? "  " : ", " ;
		}*/
		CGraphic_Device::Get_Instance()->Get_Font()->
		DrawTextW(CGraphic_Device::Get_Instance()->Get_Sprite(), 
			wss.str().c_str(), wss.str().size(), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

		wss.clear();
		wss.str(L"");
	}
}

void CTerrain::Release_GameObject()
{
	for (auto& pTile : m_vecTile)
		Safe_Delete(pTile);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTerrain::Create_Graph_Terrain()
{
	m_vecGraph.resize(m_vecTile.size()); 

	constexpr int TileCount = TILEX * TILEY;
	constexpr int DistanceMaxX = TILECX * 2;
	constexpr int DistanceMaxY = TILECY * 2;

	for (int i = 0 ; i < TILEY; ++i)
	{
		for (int j = 0 ; j < TILEX; ++j)
		{
			const int SelectIDX = j + (TILEX * i);

			const int EvenRowAdder = ((i % 2)==0) ? -1 : 0;

			const int LeftTop =SelectIDX - TILEX + EvenRowAdder;
			
			const int RightTop =LeftTop + 1 ;

			const int LeftBottom =SelectIDX + TILEX + EvenRowAdder;

			const int RightBottom = LeftBottom + 1 ;

			const std::array<int, 4ul> _IdxsCheck
			{
				LeftTop,
				RightTop,
				LeftBottom,
				RightBottom
			};

		/*	if (SelectIDX == 60)
			{

				int i = 0;
				int j = 0;
			}*/

			for (const int TargetIDX : _IdxsCheck)
			{
				if (TargetIDX < 0 || TargetIDX >(TileCount - 1))
					continue;
				if (m_vecTile[TargetIDX]->byOption == 1)
				{
					int i = 0;
					continue;
				}

				
				{
					const _vec3 CurrentTilePos = m_vecTile[SelectIDX]->vPos;
					const _vec3 TargetTilePos = m_vecTile[TargetIDX]->vPos;

					const float DistanceX = std::abs(CurrentTilePos.x - TargetTilePos.x);
					const float DistanceY = std::abs(CurrentTilePos.y - TargetTilePos.y);

					if (  DistanceX < DistanceMaxX && DistanceY < DistanceMaxY )
					{
						// 인접타일 은 존재함.
						m_vecGraph[SelectIDX].emplace_back(m_vecTile[TargetIDX]);
					}
				}
			}
		}
	}
}

CGameObject * CTerrain::Create()
{
	CGameObject* pInstance = new CTerrain;
	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}
