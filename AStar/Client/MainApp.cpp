#include "stdafx.h"
#include "MainApp.h"
#include "Player.h"
#include "GameObject_Manager.h"
#include "Scene_Manager.h"
#include "Frame_Manager.h"
#include "AStar_Manager.h"

CMainApp::CMainApp()
	:m_pGraphic_Device(CGraphic_Device::Get_Instance())
	,m_pGameObject_Manager(CGameObject_Manager::Get_Instance())
	,m_pScene_Manager(CScene_Manager::Get_Instance())
{
}



HRESULT CMainApp::Ready_MainApp()
{
	if (FAILED(m_pGraphic_Device->Ready_Graphic_Device(CGraphic_Device::MODE_WIN)))
	{
		ERR_MSG(L"Ready Graphic_Device Failed"); 
		return E_FAIL; 
	}
	if (FAILED(CScene_Manager::Get_Instance()->Scene_Change_SceneManager(SCENE_STAGE)))
		return E_FAIL; 

	if (FAILED(CTime_Manager::Get_Instance()->Ready_TimeManager()))
		return E_FAIL;

	return S_OK; 

}

void CMainApp::Update_MainApp()
{
	CTime_Manager::Get_Instance()->Compute_TimeManager();
	m_pScene_Manager->Update_SceneManager();
	CAStar_Manager::Get_Instance()->Update();

}

void CMainApp::LateUpdate_MainApp()
{
	m_pScene_Manager->Late_Update_SceneManager();
}

void CMainApp::Render_MainApp(CFrame_Manager* pFrameManager)
{
	m_pGraphic_Device->Render_Begin();
	m_pScene_Manager->Render_SceneManager();
	pFrameManager->RenderFPS(); 
	m_pGraphic_Device->Render_End();
	
}

void CMainApp::Release_MainApp()
{
	CTime_Manager::Destroy_Instance();
	CTexture_Manager::Destroy_Instance();
	m_pGameObject_Manager->Destroy_Instance();
	m_pScene_Manager->Destroy_Instance(); 
	m_pGraphic_Device->Destroy_Instance();
	
}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp; 
	if (FAILED(pInstance->Ready_MainApp()))
	{
		delete pInstance; 
		return nullptr;
	}
	return pInstance;
}

void CMainApp::Free()
{
	Release_MainApp();
	
}
