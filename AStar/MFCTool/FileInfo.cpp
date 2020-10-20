#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertReletivePath(CString strFullPath)
{
	TCHAR szReletivePath[MAX_PATH] = L""; 

	TCHAR szCurrentDirectory[MAX_PATH] = L""; 
	GetCurrentDirectory(MAX_PATH, szCurrentDirectory); 
	PathRelativePathTo(szReletivePath, szCurrentDirectory, FILE_ATTRIBUTE_DIRECTORY, strFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY); 
	return CString(szReletivePath);
}
//1. D:\�ں���\111a\FrameWork3\Texture\Stage
//2. D:\�ں���\111a\FrameWork3\Texture\Stage\Terrain\Tile\Tile0.png
void CFileInfo::DirInfoExtraction(const wstring & wstrFullPath, list<TEXPATH*>& rlistTexPath)
{
	CFileFind Find; 

	wstring wstrPath = wstrFullPath + L"\\*.*";
	//2. D:\�ں���\111a\FrameWork3\Texture\Stage\Effect\*.*
	Find.FindFile(wstrPath.c_str()); 
	BOOL bContinue = TRUE; 
	while (bContinue)
	{
		bContinue = Find.FindNextFile();
		if(Find.IsDots())
			continue;
		else if (Find.IsDirectory())
		{
			DirInfoExtraction(Find.GetFilePath().GetString(), rlistTexPath);
		}
		else
		{
			if(Find.IsSystem())
				continue;
			// ���⼭���Ͱ� ���� ���� �۾��� ��������. ���Ͽ� ������ �ߴٶ�� �Ҹ�. 
			TEXPATH* pTexInfo = new TEXPATH; 
			TCHAR szPathBuf[MAX_PATH] = L""; 
			// ������ �������� �ľ�. 
			////2. D:\�ں���\111a\FrameWork3\Texture\Stage\Terrain\Tile\Tile0.png
			lstrcpy(szPathBuf, Find.GetFilePath().GetString()); 
			////2. D:\�ں���\111a\FrameWork3\Texture\Stage\Terrain\Tile
			PathRemoveFileSpec(szPathBuf); 
			TCHAR sz������ƮŰ_������ƮŰ_�߶󳻱��[MAX_PATH] = L""; 
			lstrcpy(sz������ƮŰ_������ƮŰ_�߶󳻱��, szPathBuf); 
			pTexInfo->dwCount = FileCount(szPathBuf); 
			
			wstring wstrFileName = Find.GetFileTitle().GetString();
			//substr- ���� ������ ������ ���ڿ��� ��ȯ���ִ� �Լ�. ���� ���� ������ 
			// Tile0 -> Tile ->Tile%d.png
			wstrFileName = wstrFileName.substr(0, wstrFileName.length() - 1) + L"%d.png";
			////2. D:\�ں���\111a\FrameWork3\Texture\Stage\Terrain\\Tile\\Tile%d.png
			PathCombine(szPathBuf, szPathBuf, wstrFileName.c_str()); 
			pTexInfo->wstrRelativePath = CFileInfo::ConvertReletivePath(szPathBuf);
			////2. D:\�ں���\111a\FrameWork3\Texture\Stage\Terrain\\Tile
			pTexInfo->wstrStateKey = PathFindFileName(sz������ƮŰ_������ƮŰ_�߶󳻱��);

			PathRemoveFileSpec(sz������ƮŰ_������ƮŰ_�߶󳻱��);
			pTexInfo->wstrObjectKey = PathFindFileName(sz������ƮŰ_������ƮŰ_�߶󳻱��); 
			rlistTexPath.emplace_back(pTexInfo); 
			bContinue = FALSE;
		}
	}
}

int CFileInfo::FileCount(const wstring & wstrFullPath)
{
	CFileFind Find; 
	wstring wstrPath = wstrFullPath + L"\\*.*"; 
	BOOL bContinue = Find.FindFile(wstrPath.c_str());
	int iCount = 0; 
	while (bContinue)
	{
		bContinue = Find.FindNextFile();
		if (Find.IsDots() || Find.IsSystem())
			continue;
		++iCount;
	}
	return iCount;
}
