#pragma once
//for.MFCTool
typedef struct tagTexturePath
{
	wstring wstrRelativePath = L""; 
	wstring wstrObjectKey = L""; 
	wstring wstrStateKey = L""; 
	DWORD	dwCount =0;
}TEXPATH;
typedef struct tagTexInfo
{
	// �̹��� ������ �����ϱ� ���� �İ�ü. ��¾�� ���� HBITMAP�� ������ ������ ������ ��. 
	LPDIRECT3DTEXTURE9 pTexture; 

	// �̹����� ���� ������ ��� ���� ����ü. 
	D3DXIMAGE_INFO tImageInfo; 
}TEXINFO;
typedef struct tagTile
{
	_vec3 vPos; 
	_vec3 vSize; 
	int		iIndex; 
	int		iParentIndex; 
	BYTE byDrawID; 
	BYTE byOption; 
}TILE;

typedef struct tagUnitInfo
{
#ifdef _AFX
	CString wstrName;
#else
	wstring wstrName;
#endif // AFX
	int iAtt; 
	int iDef; 
	BYTE byJop;
	BYTE byItem; 
}UNITINFO;