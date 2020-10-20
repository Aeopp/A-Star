#pragma once
class CGameObject; 
class CGameObject_Manager
{
	DECLARE_SINGLETON(CGameObject_Manager)
private:
	CGameObject_Manager();
	~CGameObject_Manager();
public:
	CGameObject* Get_Terrain() { return m_listObject[OBJ_TERRAIN].front(); }
public:
	HRESULT Add_GameObject_Manager(OBJID eID, CGameObject* pObject);
	void	Update_GameObject_Manager();
	void	Late_Update_GameObject_Manager();
	void	Render_GameObject_Manager();
	void	Release_GameObject_Manager();

private:
	list<CGameObject*> m_listObject[OBJ_END]; 
};

