// RoomsManagerDlg.h : header file
//

#if !defined(AFX_ROOMSMANAGERDLG_H__026C4F5F_7602_412E_908E_A91C637A3282__INCLUDED_)
#define AFX_ROOMSMANAGERDLG_H__026C4F5F_7602_412E_908E_A91C637A3282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRoomsManagerDlg dialog

class CRoomsManagerDlg : public CDialog
{
// Construction
public:
	CRoomsManagerDlg::CRoomsManagerDlg(CWnd* pParent = NULL);
// Dialog Data
	//{{AFX_DATA(CRoomsManagerDlg)
	enum { IDD = IDD_ROOMSMANAGER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoomsManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRoomsManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonManageRooms();
	afx_msg void OnButtonManageTypes();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void UpdateRoomsDisplay();
	void OnRoomButtonClicked(UINT nID);
	COLORREF m_Color;
 	CBrush cBrush;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOMSMANAGERDLG_H__026C4F5F_7602_412E_908E_A91C637A3282__INCLUDED_)
