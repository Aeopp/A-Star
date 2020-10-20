#pragma once
#include "GameObject.h"
class CTerrain final : public CGameObject
{
private:
	explicit CTerrain();
public:
	virtual ~CTerrain();
public:
	vector<list<TILE*>>& Get_Graph() { return m_vecGraph; }
	vector<TILE*>& Get_Tile() { return m_vecTile; }
public:
	HRESULT LoadTerrain(const wstring& wstrFilePath); 
public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Release_GameObject() override;
public:
	void Create_Graph_Terrain(); 
public:
	static CGameObject* Create();
private:
	vector<TILE*> m_vecTile; 
	vector<list<TILE*>> m_vecGraph;

};

