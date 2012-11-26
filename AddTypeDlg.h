#if !defined(AFX_ADDTYPEDLG_H__C6146C78_CC05_4059_84F9_62A5CDD77872__INCLUDED_)
#define AFX_ADDTYPEDLG_H__C6146C78_CC05_4059_84F9_62A5CDD77872__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddTypeDlg.h : header file
//

#include <vector>
#include <string>
using namespace std;

class RoomType {
public:
	CString name;
	int charge;
	CString discribe;
	COLORREF color;
};

/////////////////////////////////////////////////////////////////////////////
// CAddTypeDlg dialog

class CAddTypeDlg : public CDialog
{
// Construction
public:
	int isEdit;
	int editPosition;
	COLORREF m_Color;
 	CBrush cBrush;

	CAddTypeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddTypeDlg)
	enum { IDD = IDD_ADDTYPE_DIALOG };
	int		m_Charge;
	CString	m_Discribe;
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddTypeDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnStaticColor();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDTYPEDLG_H__C6146C78_CC05_4059_84F9_62A5CDD77872__INCLUDED_)
