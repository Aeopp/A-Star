#pragma once
class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	static CString ConvertReletivePath(CString strFullPath);
	static void DirInfoExtraction(const wstring& wstrFullPath, list<TEXPATH*>& rlistTexPath);
	static int FileCount(const wstring& wstrFullPath);
};

