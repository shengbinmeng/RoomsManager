#if !defined(AFX_TYPESEDITDLG_H__BE80DCFD_F98A_4A53_BBEC_A157504931B0__INCLUDED_)
#define AFX_TYPESEDITDLG_H__BE80DCFD_F98A_4A53_BBEC_A157504931B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TypesEditDlg.h : header file
//

#include "AddTypeDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CTypesEditDlg dialog

class CTypesEditDlg : public CDialog
{
// Construction
public:
	CTypesEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTypesEditDlg)
	enum { IDD = IDD_TYPESEDIT_DIALOG };
	CListBox	m_List;
	CButton	m_EditButton;
	CButton	m_DelButton;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTypesEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTypesEditDlg)
	virtual void OnOK();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonEdit();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListTypes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int selectIndex;
	CString selectName;
	void UpdateList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TYPESEDITDLG_H__BE80DCFD_F98A_4A53_BBEC_A157504931B0__INCLUDED_)
