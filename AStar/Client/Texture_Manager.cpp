#include "stdafx.h"
#include "Texture_Manager.h"
#include "Single_Texture.h"
#include "Multi_Texture.h"
IMPLEMENT_SINGLETON(CTexture_Manager)
CTexture_Manager::CTexture_Manager()
{
}


CTexture_Manager::~CTexture_Manager()
{
	Release(); 
}

HRESULT CTexture_Manager::LoadImagePath(const wstring & wstrFilePath)
{
	wifstream fin; 
	fin.open(wstrFilePath);
	if (!fin.fail())
	{
		TCHAR szPath[MAX_PATH] = L"";
		TCHAR szObjectKey[MAX_PATH] = L"";
		TCHAR szStateKey[MAX_PATH] = L"";
		TCHAR szCount[MAX_PATH] = L"";
		DWORD dwCount = 0; 
		while (true)
		{
			fin.getline(szPath, MAX_PATH, '|');
			fin.getline(szObjectKey, MAX_PATH, '|');
			fin.getline(szStateKey, MAX_PATH, '|');
			fin.getline(szCount, MAX_PATH);
			dwCount = _ttoi(szCount); 
			if (fin.eof())
				break;

			if (FAILED(Insert_Texture(MULTI_TEX, szPath, szObjectKey, szStateKey, dwCount)))
			{
				ERR_MSG(L"Load ImagePath Failed"); 
				return E_FAIL; 

			}
		}
		fin.close();
	}
	return S_OK;
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
