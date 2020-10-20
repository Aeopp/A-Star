#pragma once
#include "Scene.h"
class CGameObject_Manager; 
class CStage final:
	public CScene
{
private:
	explicit CStage();
public:
	virtual ~CStage();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT Ready_Scene() override;
	virtual int Update_Scene() override;
	virtual void Late_Update_Scene() override;
	virtual void Render_Scene() override;
	virtual void Release_Scene() override;
public:
	static CScene* Create();
private:
	CGameObject_Manager* m_pGameObject_Manager; 
};

