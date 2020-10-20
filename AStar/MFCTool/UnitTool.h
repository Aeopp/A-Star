#pragma once
#include "afxwin.h"


// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 철우는 소나기인가? 
	CString m_strChange1;
	CString m_strChange2;
	
	
	// UnitData
	CString m_strName;
	int m_iAtt;
	int m_iDef;
	CListBox m_ListBox;
	CButton m_Radio[3];
	CButton m_CheckBox[3];
	map<CString, UNITINFO*> m_mapUnitInfo;
	afx_msg void OnBnClickedAddButton();
	afx_msg void OnLbnSelchangeClassName();
	afx_msg void OnBnClickedChangeString();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnEnChangeFindName();
	CString m_strFindName;
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
};
