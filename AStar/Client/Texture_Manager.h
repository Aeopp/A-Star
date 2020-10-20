#pragma once
class CTexture;
class CTexture_Manager
{
public:
	enum TEX_ID {SINGLE_TEX, MULTI_TEX};
public:
	DECLARE_SINGLETON(CTexture_Manager)
private:
	CTexture_Manager();
	~CTexture_Manager();
public:
	HRESULT LoadImagePath(const wstring& wstrFilePath); 
	const TEXINFO* Get_TexInfo(const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const DWORD& dwIndex = 0);
	HRESULT Insert_Texture(const TEX_ID eTexID, const wstring& wstrFilePath, const wstring& wstrObjectKey, const wstring& wstrStateKey = L"", const DWORD& dwIndex = 0);
	void Release(); 

private:
	
	// ���⼭�� wstring�� ������ƮŰ - ��ü - �÷��̾�, npc, ���� 1, ����2 ����3, ��� 23~
	map<wstring, CTexture*> m_mapTexture; 
};

