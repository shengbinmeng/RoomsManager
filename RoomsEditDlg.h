#if !defined(AFX_ROOMSEDITDLG_H__4488B3FF_EE96_412D_BF0A_171141691D02__INCLUDED_)
#define AFX_ROOMSEDITDLG_H__4488B3FF_EE96_412D_BF0A_171141691D02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RoomsEditDlg.h : header file
//

#include "AddRoomDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CRoomsEditDlg dialog

class CRoomsEditDlg : public CDialog
{
// Construction
public:
	CRoomsEditDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRoomsEditDlg)
	enum { IDD = IDD_ROOMSEDIT_DIALOG };
	CButton	m_EditButton;
	CButton	m_DelButton;
	CListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomsEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRoomsEditDlg)
	afx_msg void OnButtonEdit();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDelete();
	virtual void OnOK();
	afx_msg void OnSelchangeListRooms();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int selectIndex;
	CString selectName;
	void UpdateList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMSEDITDLG_H__4488B3FF_EE96_412D_BF0A_171141691D02__INCLUDED_)
