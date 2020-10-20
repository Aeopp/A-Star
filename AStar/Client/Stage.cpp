#include "stdafx.h"
#include "Stage.h"
#include "GameObject_Manager.h"
#include "Terrain.h"
#include "Player.h"

CStage::CStage()
	:m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
{
}


CStage::~CStage()
{
	Release_Scene(); 
}

HRESULT CStage::Ready_Scene()
{
	if (FAILED(CTexture_Manager::Get_Instance()->LoadImagePath(L"../Data/PathInfo.txt")))
	{
		ERR_MSG(L"Tile Image Insert Failed"); 
		return E_FAIL; 
	}
	CGameObject* pTerrain = CTerrain::Create();
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_TERRAIN, pTerrain);
	CGameObject* pObject = CPlayer::Create(); 
	m_pGameObject_Manager->Add_GameObject_Manager(OBJ_PLAYER, pObject);
	return S_OK;
}

int CStage::Update_Scene()
{
	m_pGameObject_Manager->Update_GameObject_Manager();
	return 0;
}

void CStage::Late_Update_Scene()
{
	m_pGameObject_Manager->Late_Update_GameObject_Manager();
}

void CStage::Render_Scene()
{
	m_pGameObject_Manager->Render_GameObject_Manager();
}

void CStage::Release_Scene()
{
	// 아저씨들? 왜 불리한거에는 항상 대답들을 안하시죠? 
	// 시연회 준비 잘하고 있죠? 
	// 약간 초등학생들이 방학동안 일기 쓴거 검사한다 할때의 그 반응인데... 

}

CScene * CStage::Create()
{
	CScene* pInstance = new CStage; 
	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Delete(pInstance); 
		return nullptr;
	}
	return pInstance; 
}
