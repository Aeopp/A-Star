#include "stdafx.h"
#include "Texture_Manager.h"
#include "Single_Texture.h"
#include "Multi_Texture.h"
CTexture_Manager* CTexture_Manager::m_pInstance = nullptr;
CTexture_Manager::CTexture_Manager()
{
}


CTexture_Manager::~CTexture_Manager()
{
	Release(); 
}

const TEXINFO * CTexture_Manager::Get_TexInfo(const wstring & wstrObjectKey, const wstring & wstrStateKey /*=L""*/, const DWORD & dwIndex /*= 0*/)
{
	// wstrObjectKey = Cube
	auto& iter_find = m_mapTexture.find(wstrObjectKey);
	if (m_mapTexture.end() == iter_find)
		return nullptr; 

	return iter_find->second->Get_TexInfo(wstrStateKey, dwIndex);
}

HRESULT CTexture_Manager::Insert_Texture(const TEX_ID eTexID, const wstring & wstrFilePath, const wstring & wstrObjectKey, const wstring & wstrStateKey/*=L""*/, const DWORD & dwIndex/*=0*/)
{
	auto& iter_find = m_mapTexture.find(wstrObjectKey); 
	if (m_mapTexture.end() == iter_find)
	{
		CTexture* pTexture = nullptr; 
		switch (eTexID)
		{
		case SINGLE_TEX:
			pTexture = new CSingle_Texture; 
			break; 
		case MULTI_TEX:
			pTexture = new CMulti_Texture; 
			break; 
		default:
			break;
		}
		if (FAILED(pTexture->Insert_Texture(wstrFilePath, wstrStateKey, dwIndex)))
		{
			ERR_MSG(L"Texture Insert Failed - Texture_Manager.cpp"); 
			Safe_Delete(pTexture); 
			return E_FAIL; 
		}
		m_mapTexture.emplace(wstrObjectKey, pTexture);
	}
	else if (MULTI_TEX == eTexID)
	{
		if (FAILED(m_mapTexture[wstrObjectKey]->Insert_Texture(wstrFilePath, wstrStateKey, dwIndex)))
		{
			ERR_MSG(L"MultiTexture Insert Failed - Texture_Manager.cpp");

			return E_FAIL; 
		}
	}
	return S_OK;
}

void CTexture_Manager::Release()
{
	for (auto& rPair : m_mapTexture)
		Safe_Delete(rPair.second); 
	m_mapTexture.clear(); 
}
