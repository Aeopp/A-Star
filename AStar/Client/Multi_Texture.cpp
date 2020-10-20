#include "stdafx.h"
#include "Multi_Texture.h"


CMulti_Texture::CMulti_Texture()
{
}


CMulti_Texture::~CMulti_Texture()
{
	Release(); 
}
//..\Texture\Stage\Player\Stand\AKIHA_AKI00_00%d.png
HRESULT CMulti_Texture::Insert_Texture(const wstring & wstrFilePath, const wstring & wstrStateKey , const DWORD & dwCount )
{
	auto& iter_find = m_mapMultiTex.find(wstrStateKey);

	if (iter_find != m_mapMultiTex.end())
		return E_FAIL; 

	TCHAR szFileFullPath[MAX_PATH] = L""; 
	TEXINFO* pTexInfo = nullptr; 
	for (DWORD i = 0 ; i < dwCount; ++i)
	{
		//..\Texture\Stage\Player\Stand\AKIHA_AKI00_002.png
		swprintf_s(szFileFullPath, wstrFilePath.c_str(), i);
		pTexInfo = new TEXINFO; 
		ZeroMemory(pTexInfo, sizeof(TEXINFO));

		if (FAILED(D3DXGetImageInfoFromFile(szFileFullPath, &pTexInfo->tImageInfo)))
			return E_FAIL; 
		if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
			szFileFullPath,
			pTexInfo->tImageInfo.Width,
			pTexInfo->tImageInfo.Height,
			pTexInfo->tImageInfo.MipLevels,
			0,
			pTexInfo->tImageInfo.Format,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT, 0,
			nullptr, nullptr,
			&pTexInfo->pTexture)))
		{
			Safe_Delete(pTexInfo); 
			//wstring wstrErrMsg = wstring(szFileFullPath) + L"Create Failed";
			wstring wstrErrMsg = szFileFullPath;
			wstrErrMsg += L"Create Failed";
			return E_FAIL; 
		}
		m_mapMultiTex[wstrStateKey].emplace_back(pTexInfo); 
	}
	return S_OK;
}

const TEXINFO * CMulti_Texture::Get_TexInfo(const wstring & wstrStateKey, const DWORD & dwCount)
{
	auto& iter_find = m_mapMultiTex.find(wstrStateKey);
	if (m_mapMultiTex.end() == iter_find)
		return nullptr;
	if (iter_find->second.size() <= dwCount)
		return nullptr; 

	//return m_mapMultiTex[wstrStateKey][dwCount];
	return iter_find->second[dwCount];
}

void CMulti_Texture::Release()
{
	for (auto& rPair : m_mapMultiTex)
	{
		for (auto& rTexInfo : rPair.second)
		{
			Safe_Release(rTexInfo->pTexture);
			Safe_Delete(rTexInfo);
		}

		rPair.second.clear();
		//rPair.second.swap(vector<TEXINFO*>()); 
		rPair.second.shrink_to_fit();
	}
	m_mapMultiTex.clear();
}
