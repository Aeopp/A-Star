// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strChange1(_T(""))
	, m_strChange2(_T(""))
	, m_strName(_T(""))
	, m_iAtt(0)
	, m_iDef(0)
	, m_strFindName(_T(""))
{

}

CUnitTool::~CUnitTool()
{
	for (auto& rPair : m_mapUnitInfo)
		Safe_Delete(rPair.second);

	m_mapUnitInfo.clear(); 
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strChange1);
	DDX_Text(pDX, IDC_EDIT2, m_strChange2);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_iAtt);
	DDX_Text(pDX, IDC_EDIT5, m_iDef);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_RADIO1, m_Radio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_Radio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_Radio[2]);

	DDX_Control(pDX, IDC_CHECK1, m_CheckBox[0]);
	DDX_Control(pDX, IDC_CHECK2, m_CheckBox[1]);
	DDX_Control(pDX, IDC_CHECK3, m_CheckBox[2]);

	DDX_Text(pDX, IDC_EDIT6, m_strFindName);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedChangeString)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnBnClickedAddButton)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnLbnSelchangeClassName)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTool::OnBnClickedDelete)
	ON_EN_CHANGE(IDC_EDIT6, &CUnitTool::OnEnChangeFindName)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnBnClickedLoad)
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnBnClickedChangeString()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//UpdateData(TRUE); 
	m_strChange2 = L"������ �������ΰ� �������ΰ�? ";
	UpdateData(FALSE);
}


void CUnitTool::OnBnClickedAddButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	auto& iter_find = m_mapUnitInfo.find(m_strName);
	if (m_mapUnitInfo.end() != iter_find)
		return; 

	UNITINFO* pUnit = new UNITINFO; 
	pUnit->wstrName = m_strName; 
	pUnit->iAtt = m_iAtt; 
	pUnit->iDef = m_iDef; 
	pUnit->byItem = 0; 
	int i = 0;
	for (; i < 3; ++i)
	{
		if(m_Radio[i].GetCheck())
			break;
	}
	pUnit->byJop = i;

	// ���� �������� �ִ��� �������� �Ǻ�����. 
	// 0000 0010 -> ByItme 
	// byItem |= 
	//	0000 0111 
	//& 0000 0001
	//  0000 0000
	if (m_CheckBox[0].GetCheck())
		pUnit->byItem |= SWORD;
	if (m_CheckBox[1].GetCheck())
		pUnit->byItem |= �Ź�;
	if (m_CheckBox[2].GetCheck())
		pUnit->byItem |= �縻;

	m_ListBox.AddString(m_strName);
	m_mapUnitInfo.emplace(pUnit->wstrName, pUnit); 
	UpdateData(FALSE); 

}


void CUnitTool::OnLbnSelchangeClassName()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	for (int i = 0; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE);
		m_CheckBox[i].SetCheck(FALSE); 
	}
	int iIndex = m_ListBox.GetCurSel();
	if (-1 == iIndex)
		return; 
	CString strFindName;
	m_ListBox.GetText(iIndex, strFindName);

	auto& iter_find = m_mapUnitInfo.find(strFindName);
	if (m_mapUnitInfo.end() == iter_find)
		return; 

	m_strName = iter_find->second->wstrName; 
	m_iAtt = iter_find->second->iAtt; 
	m_iDef = iter_find->second->iDef; 
	m_Radio[iter_find->second->byJop].SetCheck(TRUE);
	//0000 0100
	//0000 0001
	//0000 0010
	//0000 0100
	if (iter_find->second->byItem & SWORD)
		m_CheckBox[0].SetCheck(TRUE);
	if (iter_find->second->byItem & �Ź�)
		m_CheckBox[1].SetCheck(TRUE);
	if (iter_find->second->byItem & �縻)
		m_CheckBox[2].SetCheck(TRUE);
	UpdateData(FALSE); 
}


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_Radio[0].SetCheck(TRUE); 
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CUnitTool::OnBnClickedDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE); 
	int iIndex = m_ListBox.GetCurSel(); 
	if (LB_ERR == iIndex)
		return; 
	CString wstrFindName = L""; 
	m_ListBox.GetText(iIndex, wstrFindName); 
	auto& iter_find = m_mapUnitInfo.find(wstrFindName); 
	if (iter_find == m_mapUnitInfo.end())
		return; 
	Safe_Delete(iter_find->second); 
	m_mapUnitInfo.erase(iter_find); 
	m_ListBox.DeleteString(iIndex); 
	UpdateData(FALSE); 
}


void CUnitTool::OnEnChangeFindName()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	auto& iter_Find = m_mapUnitInfo.find(m_strFindName);
	if (iter_Find == m_mapUnitInfo.end())
		return; 

	int iIndex = m_ListBox.FindString(0, m_strFindName);
	if (LB_ERR == iIndex)
		return; 
	m_ListBox.SetCurSel(iIndex);
	m_strName = iter_Find->second->wstrName; 
	m_iAtt = iter_Find->second->iAtt; 
	m_iDef = iter_Find->second->iDef; 

	for (int i = 0 ; i < 3; ++i)
	{
		m_Radio[i].SetCheck(FALSE); 
		m_CheckBox[i].SetCheck(FALSE); 
	}
	m_Radio[iter_Find->second->byJop].SetCheck(TRUE);
	//0000 0100
	//0000 0001
	//0000 0010
	//0000 0100
	if (iter_Find->second->byItem & SWORD)
		m_CheckBox[0].SetCheck(TRUE);
	if (iter_Find->second->byItem & �Ź�)
		m_CheckBox[1].SetCheck(TRUE);
	if (iter_Find->second->byItem & �縻)
		m_CheckBox[2].SetCheck(TRUE);
	UpdateData(FALSE); 
}


void CUnitTool::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(FALSE,// ��� ���� -true��� ������, false��� ������
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) |*.dat||",this);
	TCHAR szPath[MAX_PATH] = L"";
	//D:\�ں���\111a\FrameWork3
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
		for (auto& MyPair : m_mapUnitInfo)
		{
			dwStrByte = (MyPair.first.GetLength() + 1) * sizeof(TCHAR);

			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr); 
			WriteFile(hFile, MyPair.first.GetString(), dwStrByte, &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->iAtt, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->iDef, sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->byJop, sizeof(BYTE), &dwByte, nullptr);
			WriteFile(hFile, &MyPair.second->byItem, sizeof(BYTE), &dwByte, nullptr);
		}
		CloseHandle(hFile); 
	}
}


void CUnitTool::OnBnClickedLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(TRUE,// ��� ���� -true��� ������, false��� ������
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data File(*.dat) |*.dat||", this);
	TCHAR szPath[MAX_PATH] = L"";
	//D:\�ں���\111a\FrameWork3
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString strFilePath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (INVALID_HANDLE_VALUE == hFile)
			return;
		DWORD dwStrByte = 0;
		DWORD dwByte = 0;
		UNITINFO* pUnit = nullptr; 
		while(true)
		{
			pUnit = new UNITINFO;
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			TCHAR* pszBuf = new TCHAR[dwStrByte];
			ReadFile(hFile, pszBuf, dwStrByte, &dwByte, nullptr);
			pUnit->wstrName = pszBuf; 
			delete[] pszBuf; 

			ReadFile(hFile, &pUnit->iAtt, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &pUnit->iDef, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &pUnit->byJop, sizeof(BYTE), &dwByte, nullptr);
			ReadFile(hFile, &pUnit->byItem, sizeof(BYTE), &dwByte, nullptr);

			if (0 == dwByte)
			{
				Safe_Delete(pUnit); 
				break; 
			}

			m_mapUnitInfo.emplace(pUnit->wstrName, pUnit); 
			m_ListBox.AddString(pUnit->wstrName);
		}
		CloseHandle(hFile);
	}
}
