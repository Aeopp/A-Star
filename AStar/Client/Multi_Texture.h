#pragma once
#include "Texture.h"
class CMulti_Texture final :
	public CTexture
{
public:
	explicit CMulti_Texture();
	virtual ~CMulti_Texture();
public:
	// CTexture��(��) ���� ��ӵ�
	virtual HRESULT Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey , const DWORD & dwCount ) override;
	virtual const TEXINFO * Get_TexInfo(const wstring & wstrStateKey , const DWORD & dwCount ) override;
	virtual void Release() override;
private:
	//���⿡�� wstring�� StateKey- �ൿ - �ȴ�, �ٴ�, �״�, ������ ���... 
	map<wstring, vector<TEXINFO*>> m_mapMultiTex; 

};

