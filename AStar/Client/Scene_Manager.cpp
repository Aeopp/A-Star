#include "stdafx.h"
#include "Scene_Manager.h"
#include "Stage.h"

IMPLEMENT_SINGLETON(CScene_Manager)
CScene_Manager::CScene_Manager()
	:m_eNextScene(SCENE_END)
	,m_eCurrentScene(SCENE_END)
{
}


CScene_Manager::~CScene_Manager()
{
	Release_SceneManager();
}

HRESULT CScene_Manager::Scene_Change_SceneManager(SCENEID eNextSceneID)
{
	m_eNextScene = eNextSceneID; 
	if (m_eCurrentScene != m_eNextScene)
	{
		Safe_Delete(m_pCurrentScene); 
		switch (m_eNextScene)
		{
		case SCENE_LOADING:
			//m_pCurrentScene = new CScene; 
			break;
		case SCENE_STAGE:
			m_pCurrentScene = CStage::Create(); 
			break;
		case SCENE_BOSS:
			break;
		default:
			return E_FAIL;
		}
		m_eCurrentScene = m_eNextScene; 
	}

	return S_OK;
}

int CScene_Manager::Update_SceneManager()
{
	m_pCurrentScene->Update_Scene();
	return 0;
}

void CScene_Manager::Late_Update_SceneManager()
{
	m_pCurrentScene->Late_Update_Scene();
}

void CScene_Manager::Render_SceneManager()
{
	m_pCurrentScene->Render_Scene();
}

void CScene_Manager::Release_SceneManager()
{
	Safe_Delete(m_pCurrentScene);
}
