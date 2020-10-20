// MyForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnBnClickedUnitTool)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyForm::OnBnClickedMapTool)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyForm::OnBnClickedExtractionPath)
END_MESSAGE_MAP()


// CMyForm �����Դϴ�.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm �޽��� ó�����Դϴ�.


void CMyForm::OnBnClickedUnitTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_tUnitTool.GetSafeHwnd() == nullptr)
		m_tUnitTool.Create(IDD_UNITTOOL);
	m_tUnitTool.ShowWindow(SW_SHOW); 
	//ERR_MSG(L"������ �����ΰ� !");
}


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_tFont.CreatePointFont(150, L"�����ý��丮");
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_tFont);
}


void CMyForm::OnBnClickedMapTool()
{
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_tMapTool.GetSafeHwnd())
		m_tMapTool.Create(IDD_MAPTOOL);

	m_tMapTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedExtractionPath()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_tExtractionPath.GetSafeHwnd())
		m_tExtractionPath.Create(IDD_EXTRACTIONPATH); 

	m_tExtractionPath.ShowWindow(SW_SHOW); 
}
