// MyForm.cpp : 구현 파일입니다.
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


// CMyForm 진단입니다.

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


// CMyForm 메시지 처리기입니다.


void CMyForm::OnBnClickedUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_tUnitTool.GetSafeHwnd() == nullptr)
		m_tUnitTool.Create(IDD_UNITTOOL);
	m_tUnitTool.ShowWindow(SW_SHOW); 
	//ERR_MSG(L"현수는 정수인가 !");
}


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_tFont.CreatePointFont(150, L"메이플스토리");
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_tFont);
}


void CMyForm::OnBnClickedMapTool()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == m_tMapTool.GetSafeHwnd())
		m_tMapTool.Create(IDD_MAPTOOL);

	m_tMapTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedExtractionPath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == m_tExtractionPath.GetSafeHwnd())
		m_tExtractionPath.Create(IDD_EXTRACTIONPATH); 

	m_tExtractionPath.ShowWindow(SW_SHOW); 
}
