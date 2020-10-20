#pragma once
#include "Texture.h"
class CMulti_Texture final :
	public CTexture
{
public:
	explicit CMulti_Texture();
	virtual ~CMulti_Texture();
public:
	// CTexture을(를) 통해 상속됨
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey , const DWORD & dwCount ) override;
	virtual const TEXINFO * Get_TexInfo(const wstring & wstrStateKey , const DWORD & dwCount ) override;
	virtual void Release() override;
private:
	//여기에서 wstring은 StateKey- 행동 - 걷다, 뛰다, 죽다, 때리다 등등... 
	map<wstring, vector<TEXINFO*>> m_mapMultiTex; 

};

