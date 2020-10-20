#pragma once
class CMFCToolView;
class CTerrain
{
public:
	CTerrain();
	~CTerrain();
public:
	vector<TILE*>& Get_Tile() { return m_vecTile; }
	void Set_View(CMFCToolView* pView) { m_pView = pView; }
public:
	void TileChange_Terrain(const _vec3& vPos, const BYTE& byDrawID, const BYTE& byOption = 0);
	int Get_TileIndex(const _vec3& vPos);
	bool IsPicking(const _vec3& vPos, const int& iIndex);
	void Set_Ratio(_matrix& matWorld, float fRatioX, float fRatioY);
public:
	HRESULT Ready_Terrain(); 
	void Render_Terrain(); 
	void Mini_Render_Terrain();
	void Release(); 


private:
	vector<TILE*> m_vecTile; 
	CMFCToolView* m_pView; 
};

