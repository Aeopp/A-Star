// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "MFCToolView.h"
#include "Terrain.h"


// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent)
{
	m_iDrawID = 0; 
}

CMapTool::~CMapTool()
{
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_WM_DROPFILES()
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnLbnSelchangePicture)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnBnClickedSave)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	//0001
	//1110
	//1111 1111 1111 1111 1111 1111
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE); 
	TCHAR szFilePath[MAX_PATH] = L"";
	TCHAR szFileName[MAX_PATH] = L"";
	CString strReletivePath = L""; 
	int iSize = DragQueryFile(hDropInfo, -1, nullptr, 0);
	CString strFileNameAndExtant = L""; 
	for (int i = 0; i < iSize; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
		strReletivePath = CFileInfo::ConvertReletivePath(szFilePath); 
		strFileNameAndExtant = PathFindFileName(strReletivePath); 
		lstrcpy(szFileName, strFileNameAndExtant.GetString());
		PathRemoveExtension(szFileName); 
		m_ListBox.AddString(szFileName);

	}
	HorizontalScroll();
	UpdateData(FALSE); 
	CDialog::OnDropFiles(hDropInfo);
}

void CMapTool::HorizontalScroll()
{
	CString strName; 
	CSize tSize; 
	int iCX = 0; 
	CDC* pDC = m_ListBox.GetDC();
	for (int i = 0 ; i < m_ListBox.GetCount(); ++i)
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


void CMapTool::OnLbnSelchangePicture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE); 
	CString strFindName = L""; 
	int iIndex = m_ListBox.GetCurSel(); 
	if (LB_ERR == iIndex)
		return; 

	m_ListBox.GetText(iIndex, strFindName); 

	int i = 0; 
	for (; i < strFindName.GetLength(); ++i)
	{
		if(isdigit(strFindName[i]))
			break;
	}

	strFindName.Delete(0, i);

	m_iDrawID = _wtoi(strFindName.GetString()); 

	CGraphic_Device::Get_Instance()->Render_Begin();
	D3DXMATRIX matSacle, matTrans, matWorld; 
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", m_iDrawID);
	if (nullptr == pTexInfo)
		return; 
	float fCenterX = pTexInfo->tImageInfo.Width >> 1; 
	float fCenterY = pTexInfo->tImageInfo.Height >> 1; 
	
	D3DXMatrixTranslation(&matTrans, float(WINCX >> 1), float(WINCY >> 1), 0.f);
	float fSizeX = WINCX / float(TILECX);
	float fSizeY = WINCY / float(TILECY);
	D3DXMatrixScaling(&matSacle, fSizeX, fSizeY, 0.f);
	matWorld = matSacle * matTrans; 
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255)); 


	CGraphic_Device::Get_Instance()->Render_End(m_Picture.GetSafeHwnd());
	UpdateData(FALSE); 

}


void CMapTool::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE,// 모드 지정 -true라면 열기모드, false라면 저장모드
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) |*.dat||", this);
	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;
	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strFilePath, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		DWORD dwStrByte = 0;
		DWORD dwByte = 0;
		CMainFrame* pMain = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd()); 
		CMFCToolView* pView = dynamic_cast<CMFCToolView*>(pMain->m_tMainSplitter.GetPane(0, 1));
		vector<TILE*>& vecTile = pView->m_pTerrain->Get_Tile(); 
		for (auto& pTile : vecTile)
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);
		CloseHandle(hFile);
	}
}
