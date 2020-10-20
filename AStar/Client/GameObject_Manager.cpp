#include "stdafx.h"
#include "GameObject_Manager.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CGameObject_Manager)

CGameObject_Manager::CGameObject_Manager()
{
}


CGameObject_Manager::~CGameObject_Manager()
{
	Release_GameObject_Manager();
}

HRESULT CGameObject_Manager::Add_GameObject_Manager(OBJID eID, CGameObject * pObject)
{
	m_listObject[eID].emplace_back(pObject); 
	return S_OK;
}

void CGameObject_Manager::Update_GameObject_Manager()
{
	for (int i = 0 ; i < OBJ_END ; ++i)
	{
		auto& iter = m_listObject[i].begin(); 
		for (; iter != m_listObject[i].end();)
		{
			int iEvent = (*iter)->Update_GameObject(); 
			if (OBJ_DEAD == iEvent)
			{
				Safe_Delete(*iter);
				iter = m_listObject[i].erase(iter);
			}
			else
				++iter; 
		}
	}
}

void CGameObject_Manager::Late_Update_GameObject_Manager()
{
	for (int i = 0 ; i < OBJ_END ; ++i)
	{
		for (CGameObject*& pGameObject : m_listObject[i])
		{
			pGameObject->Late_Update_GameObject();
		}
	}
}

void CGameObject_Manager::Render_GameObject_Manager()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (CGameObject*& pGameObject : m_listObject[i])
		{
			pGameObject->Render_GameObject();
		}
	}
}

void CGameObject_Manager::Release_GameObject_Manager()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (CGameObject*& pGameObject : m_listObject[i])
			Safe_Delete(pGameObject);

		m_listObject[i].clear();
	}
}

