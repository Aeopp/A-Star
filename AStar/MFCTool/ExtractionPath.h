#pragma once
#include "afxwin.h"


// CExtractionPath ��ȭ �����Դϴ�.

class CExtractionPath : public CDialog
{
	DECLARE_DYNAMIC(CExtractionPath)

public:
	CExtractionPath(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CExtractionPath();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXTRACTIONPATH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_ListBox;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	void HorizontalScroll();
	list<TEXPATH*> m_listTexPath; 
	afx_msg void OnBnClickedSavebutton();
	afx_msg void OnBnClickedLoadbutton();
};
