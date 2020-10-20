#pragma once
#include "afxwin.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// ö��� �ҳ����ΰ�? 
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
