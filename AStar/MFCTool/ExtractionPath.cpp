// ExtractionPath.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "ExtractionPath.h"
#include "afxdialogex.h"
#include "FileInfo.h"

// CExtractionPath 대화 상자입니다.

IMPLEMENT_DYNAMIC(CExtractionPath, CDialog)

CExtractionPath::CExtractionPath(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EXTRACTIONPATH, pParent)
{

}

CExtractionPath::~CExtractionPath()
{
}

void CExtractionPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(CExtractionPath, CDialog)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDSAVEBUTTON, &CExtractionPath::OnBnClickedSavebutton)
	ON_BN_CLICKED(IDLOADBUTTON, &CExtractionPath::OnBnClickedLoadbutton)
END_MESSAGE_MAP()


// CExtractionPath 메시지 처리기입니다.


void CExtractionPath::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE); 
	TCHAR szFullPath[MAX_PATH] = L""; 
	int iSize = DragQueryFile(hDropInfo, -1, nullptr, 0); 
	for (int i = 0 ; i < iSize ; ++i)
	{
		DragQueryFile(hDropInfo, i, szFullPath, MAX_PATH); 
		// 작업을 싹 할것. 
		CFileInfo::DirInfoExtraction(szFullPath, m_listTexPath); 
	}
	m_ListBox.ResetContent(); 
	wstring wstrCombine = L""; 
	TCHAR szCount[MAX_PATH] = L""; 

	for (auto& pTexPath : m_listTexPath)
	{
		_itow_s(pTexPath->dwCount, szCount, 10);
		wstrCombine = pTexPath->wstrRelativePath + L"|" + pTexPath->wstrObjectKey + L"|" + pTexPath->wstrStateKey + L"|" + szCount;
		m_ListBox.AddString(wstrCombine.c_str()); 
	}
	HorizontalScroll();
	UpdateData(FALSE);
	CDialog::OnDropFiles(hDropInfo);
}

void CExtractionPath::HorizontalScroll()
{
	CString strName;
	CSize tSize;
	int iCX = 0;
	CDC* pDC = m_ListBox.GetDC();
	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);
		tSize = pDC->GetTextExtent(strName);

		if (tSize.cx > iCX)
			iCX = tSize.cx;
	}
	m_ListBox.ReleaseDC(pDC);

	if (iCX > m_ListBox.GetHorizontalExtent())
	{
		m_ListBox.SetHorizontalExtent(iCX);
	}
}


void CExtractionPath::OnBnClickedSavebutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//파일 입출력을 하기 위한 객체 생성! 
	wofstream fout; 
	fout.open("../Data/PathInfo.txt");
	if (!fout.fail())
	{
		for (auto& pTexPath : m_listTexPath)
		{
			fout << pTexPath->wstrRelativePath << L"|" << pTexPath->wstrObjectKey << L"|" << pTexPath->wstrStateKey << L"|" << pTexPath->dwCount << endl; 

		}
		fout.close();
	}
	WinExec("notepad.exe ../Data/PathInfo.txt", SW_SHOW); 
}


void CExtractionPath::OnBnClickedLoadbutton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); 
	wifstream fin; 
	fin.open("../Data/PathInfo.txt"); 
	if (!fin.fail())
	{
		TCHAR szPath[MAX_PATH] = L""; 
		TCHAR szObjectKey[MAX_PATH] = L"";
		TCHAR szStateKey[MAX_PATH] = L"";
		TCHAR szCount[MAX_PATH] = L"";
		m_ListBox.ResetContent(); 
		wstring wstrCombine = L"";
		while (true)
		{
			fin.getline(szPath, MAX_PATH, '|');
			fin.getline(szObjectKey, MAX_PATH, '|');
			fin.getline(szStateKey, MAX_PATH, '|');
			fin.getline(szCount, MAX_PATH);
			if (fin.eof())
				break; 
			wstrCombine = wstring(szPath) + L"|" + szObjectKey + L"|" + szStateKey + L"|" + szCount;
			m_ListBox.AddString(wstrCombine.c_str());
		}
		fin.close(); 
	}
	HorizontalScroll();
	UpdateData(FALSE);
}
