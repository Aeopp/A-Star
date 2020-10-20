#pragma once
class CGameObject_Manager;
class CScene_Manager;
class CFrame_Manager; 
class CMainApp
{
private:
	explicit CMainApp();
public:
	virtual ~CMainApp() = default; //== virtual ~CMainApp() = default; 

public :
	HRESULT Ready_MainApp();
	void Update_MainApp(); 
	void LateUpdate_MainApp(); 
	void Render_MainApp(CFrame_Manager* pFrameManager);
	void Release_MainApp(); 

public :
	static CMainApp* Create(); 
	void Free(); 
private:
	CGraphic_Device* m_pGraphic_Device; 
	CGameObject_Manager* m_pGameObject_Manager; 
	CScene_Manager* m_pScene_Manager; 
};

