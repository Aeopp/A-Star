#pragma once
// for.Client
typedef struct tagTexturePath
{
	wstring wstrRelativePath = L"";
	wstring wstrObjectKey = L"";
	wstring wstrStateKey = L"";
	DWORD	dwCount = 0;
}TEXPATH;
typedef struct tagTexInfo
{
	// 이미지 한장을 제어하기 위한 컴객체. 예쩐에 쓰던 HBITMAP과 동일한 역할을 수행할 것. 
	LPDIRECT3DTEXTURE9 pTexture; 

	// 이미지에 대한 정보를 담고 있을 구조체. 
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
typedef struct tagInfo 
{
	_vec3 vPos; 
	_vec3 vSize; 
	_vec3 vDir; 

}INFO;
typedef struct tagFrame
{
	float fStartFrame; 
	float fEndFrame; 
}FRAME; 

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