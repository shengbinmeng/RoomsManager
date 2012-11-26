// RoomsEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomsManager.h"
#include "RoomsEditDlg.h"
#include "AddRoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern vector<Room*> all_rooms;
extern vector<RoomType*> all_types;

/////////////////////////////////////////////////////////////////////////////
// CRoomsEditDlg dialog

CRoomsEditDlg::CRoomsEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoomsEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomsEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	selectIndex = -1;
	selectName = "";
}


void CRoomsEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomsEditDlg)
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_EditButton);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_DelButton);
	DDX_Control(pDX, IDC_LIST_ALL_ROOMS, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRoomsEditDlg, CDialog)
	//{{AFX_MSG_MAP(CRoomsEditDlg)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_LBN_SELCHANGE(IDC_LIST_ROOMS, OnSelchangeListRooms)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRoomsEditDlg message handlers
void CRoomsEditDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CRoomsEditDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	if(all_types.size() <= 0) {
		MessageBox("还没有房间类别，请先添加房间类别。");
		return;
	}
	CAddRoomDlg dlg;
	if(dlg.DoModal() == IDOK) {
		UpdateList();
	}
}

void CRoomsEditDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	if(selectName == "") {
		MessageBox("未选择项！");
		return;
	}

	for (int i = 0; i < all_rooms.size(); ++i) {
		if (all_rooms[i]->name == selectName) {
			if (all_rooms[i]->user_count > 0) {
				MessageBox("该房间还有人住, 不能删除。请先清除入住用户。", NULL, MB_ICONINFORMATION|MB_OK|MB_DEFBUTTON2);
				return;
			} else {
				if(MessageBox("确认要删除："+selectName+" ?",NULL,MB_ICONINFORMATION|MB_YESNO|MB_DEFBUTTON2) == IDNO) return;
				else {
					delete all_rooms[i];
					all_rooms.erase(all_rooms.begin() + i);
					selectIndex -= 1;
					UpdateList();
				}
			}

			break ;
		}
	}
}

void CRoomsEditDlg::OnButtonEdit() 
{
	// TODO: Add your control notification handler code here
	if(selectName == "") {
		MessageBox("未选择项！");
		return;
	}
	CAddRoomDlg dlg;
	dlg.isEdit = 1;
	dlg.m_Name = selectName;
	if (dlg.DoModal() == IDOK) {
		UpdateList();	
	}
}

void CRoomsEditDlg::UpdateList()
{
	m_List.ResetContent();

	for(int i = 0; i < all_rooms.size(); ++i){   
		m_List.AddString(all_rooms[i]->name);
	}
	m_List.SetCurSel(selectIndex);

	UpdateData(false);
	OnSelchangeListRooms();
	if(all_rooms.size() == 0) {
		MessageBox("列表为空！");
	}
}

void CRoomsEditDlg::OnSelchangeListRooms() 
{
	// TODO: Add your control notification handler code here
	selectIndex = m_List.GetCurSel();
	if(selectIndex >= 0) m_List.GetText (selectIndex, selectName);
	else selectName = "";
}

BOOL CRoomsEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
