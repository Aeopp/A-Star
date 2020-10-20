#pragma once
#include "afxwin.h"


// CExtractionPath 대화 상자입니다.

class CExtractionPath : public CDialog
{
	DECLARE_DYNAMIC(CExtractionPath)

public:
	CExtractionPath(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CExtractionPath();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXTRACTIONPATH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void HorizontalScroll();
	list<TEXPATH*> m_listTexPath; 
	afx_msg void OnBnClickedSavebutton();
	afx_msg void OnBnClickedLoadbutton();
};
