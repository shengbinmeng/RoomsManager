// AddRoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomsManager.h"
#include "AddRoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	vector<Room*> all_rooms;
extern	vector<RoomType*> all_types;

/////////////////////////////////////////////////////////////////////////////
// CAddRoomDlg dialog


CAddRoomDlg::CAddRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddRoomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddRoomDlg)
	m_Name = _T("");
	m_Discribe = _T("");
	m_Charge = 0;
	//}}AFX_DATA_INIT

	isEdit = 0;
	editPosition = -1;
}


void CAddRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddRoomDlg)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_TypeCombo);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_DISCRIBE, m_Discribe);
	DDX_Text(pDX, IDC_EDIT_CHARGE, m_Charge);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddRoomDlg, CDialog)
	//{{AFX_MSG_MAP(CAddRoomDlg)
	ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeComboType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddRoomDlg message handlers

BOOL CAddRoomDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	for (int i = 0; i < all_types.size(); ++i) {
		m_TypeCombo.AddString(all_types[i]->name);
	}

	if(isEdit) {
		for (int i = 0; i < all_rooms.size(); ++i){
			if (all_rooms[i]->name == m_Name) {
				m_Charge = all_rooms[i]->charge;
				m_Discribe = all_rooms[i]->discribe;
				editPosition = i;
				m_TypeCombo.SelectString(0, all_rooms[i]->type_name);
				break;
			}
		}
	} else {
		m_TypeCombo.SetCurSel(0);
		CString select;
		m_TypeCombo.GetLBText(0, select);
		for(int i = 0; i < all_types.size(); ++i) {
			if(all_types[i]->name == select) {
				m_Charge = all_types[i]->charge;
				m_Discribe = all_types[i]->discribe;
				break;
			}
		}
	}

	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddRoomDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);

	if((m_Name == "") || (m_Charge == -1) || (m_Discribe == "")) {
		MessageBox("请输入完整的信息！");
		return ;
	}

	for(int i = 0; i < all_rooms.size(); ++i) {
		if(all_rooms[i]->name == m_Name) {
			if (isEdit && i == editPosition) continue;
			else break;
		}
	}

	if(i < all_rooms.size()) {
		MessageBox("此名称已存在!");
		return ;
	}
	else
	{
		CString select;
		m_TypeCombo.GetLBText(m_TypeCombo.GetCurSel(), select);
		if (isEdit) {
			Room *room = all_rooms[editPosition];
			room->name = m_Name;
			room->charge = m_Charge;
			room->discribe = m_Discribe;
			room->type_name = select;
		} else {
			Room *room = new Room;
			room->name = m_Name;
			room->charge = m_Charge;
			room->discribe = m_Discribe;
			room->type_name = select;
			all_rooms.push_back(room);
		}

		CDialog::OnOK();
	}

}


void CAddRoomDlg::OnSelchangeComboType() 
{
	// TODO: Add your control notification handler code here
	if(isEdit) return;
	UpdateData(true);

	CString select;
	m_TypeCombo.GetLBText(m_TypeCombo.GetCurSel(), select);
	for(int i = 0; i < all_types.size(); ++i) {
		if(all_types[i]->name == select) {
			m_Charge = all_types[i]->charge;
			m_Discribe = all_types[i]->discribe;
			break;
		}
	}

	UpdateData(false);
}
