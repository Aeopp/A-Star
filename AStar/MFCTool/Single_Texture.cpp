#include "stdafx.h"
#include "Single_Texture.h"


CSingle_Texture::CSingle_Texture()
{
}


CSingle_Texture::~CSingle_Texture()
{
	Release(); 
}

HRESULT CSingle_Texture::Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey /*= L""*/, const DWORD & dwCount /*= 0*/)
{
	ZeroMemory(&m_tTexInfo, sizeof(TEXINFO)); 

	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_tTexInfo.tImageInfo)))
		return E_FAIL; 
	if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
		wstrFilePath.c_str(),
		m_tTexInfo.tImageInfo.Width,
		m_tTexInfo.tImageInfo.Height,
		m_tTexInfo.tImageInfo.MipLevels,
		0,
		m_tTexInfo.tImageInfo.Format,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		nullptr,
		nullptr,
		&m_tTexInfo.pTexture)))
	{
		ERR_MSG(L"Create Texture Failed! - SingleTexture.cpp");
		return E_FAIL;
	}
	return S_OK;
}

const TEXINFO * CSingle_Texture::Get_TexInfo(const wstring & wstrStateKey /*= L""*/, const DWORD & dwCount /*= 0*/)
{
	return &m_tTexInfo;
}

void CSingle_Texture::Release()
{
	Safe_Release(m_tTexInfo.pTexture);
}
