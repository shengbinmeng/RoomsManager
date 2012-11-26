#if !defined(AFX_ADDROOMDLG_H__AC69EE6C_095E_4E13_B5B3_7AABE2DFC91F__INCLUDED_)
#define AFX_ADDROOMDLG_H__AC69EE6C_095E_4E13_B5B3_7AABE2DFC91F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddRoomDlg.h : header file
//

#include <vector>
#include <string>
using namespace std;
#include "AddTypeDlg.h"

class Room {
public:
	CString name;
	CString type_name;
	int charge;
	CString discribe;
	int user_count;
	CString user_name;
	CString user_id;
	CString note;
	int user_prepay;
	CString use_time;
	Room() {
		charge = 0;
		user_count = 0;
		user_prepay = 0;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CAddRoomDlg dialog

class CAddRoomDlg : public CDialog
{
// Construction
public:
	int isEdit;
	int editPosition;
	CAddRoomDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddRoomDlg)
	enum { IDD = IDD_ADDROOM_DIALOG };
	CComboBox	m_TypeCombo;
	CString	m_Name;
	CString	m_Discribe;
	int		m_Charge;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddRoomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddRoomDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDROOMDLG_H__AC69EE6C_095E_4E13_B5B3_7AABE2DFC91F__INCLUDED_)
