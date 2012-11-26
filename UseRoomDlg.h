#if !defined(AFX_USEROOMDLG_H__6CCB3FB6_F905_47A4_981D_390E74221E86__INCLUDED_)
#define AFX_USEROOMDLG_H__6CCB3FB6_F905_47A4_981D_390E74221E86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UseRoomDlg.h : header file
//

#include "AddRoomDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CUseRoomDlg dialog

class CUseRoomDlg : public CDialog
{
// Construction
public:
	int roomIndex;
	Room *theRoom;
	CUseRoomDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUseRoomDlg)
	enum { IDD = IDD_USEROOM_DIALOG };
	CDateTimeCtrl	m_InTime;
	CString	m_Note;
	int		m_Prepay;
	CString	m_UserID;
	CString	m_UserName;
	CString	m_Title;
	int		m_Charge;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUseRoomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUseRoomDlg)
	afx_msg void OnButtonClear();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USEROOMDLG_H__6CCB3FB6_F905_47A4_981D_390E74221E86__INCLUDED_)
