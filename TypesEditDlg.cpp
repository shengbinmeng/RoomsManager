// TypesEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomsManager.h"
#include "TypesEditDlg.h"
#include "AddRoomDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern vector<RoomType*> all_types;
extern vector<Room*> all_rooms;

/////////////////////////////////////////////////////////////////////////////
// CTypesEditDlg dialog


CTypesEditDlg::CTypesEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTypesEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTypesEditDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	selectIndex = -1;
	selectName = "";
}


void CTypesEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTypesEditDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_BUTTON_EDIT, m_EditButton);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_DelButton);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTypesEditDlg, CDialog)
	//{{AFX_MSG_MAP(CTypesEditDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_LBN_SELCHANGE(IDC_LIST_TYPES, OnSelchangeListTypes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTypesEditDlg message handlers

void CTypesEditDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CTypesEditDlg::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	CAddTypeDlg dlg;
	if(dlg.DoModal() == IDOK) {
		UpdateList();
	}
}

void CTypesEditDlg::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	if(selectName == "") {
		MessageBox("未选择项！");
		return;
	}

	CString str = "";
	for (int i = 0; i < all_rooms.size(); ++i) {
		if (all_rooms[i]->type_name == selectName) {
			str += "(" + all_rooms[i]->name + ") ";
		}
	}
	if (str != "") {
		MessageBox("该类型中还包含以下房间： " + str +" , 不能删除。", NULL, MB_ICONINFORMATION|MB_OK|MB_DEFBUTTON2);
		return;
	}

	int n = MessageBox("确认要删除："+selectName+" ?",NULL,MB_ICONINFORMATION|MB_YESNO|MB_DEFBUTTON2);
	if(n == IDNO) return;
	else {
		for (int i = 0; i < all_types.size(); ++i) {
			if (all_types[i]->name == selectName) {
				delete all_types[i];
				all_types.erase(all_types.begin() + i);
			}
		}
		selectIndex -= 1;
		UpdateList();
	}
}

void CTypesEditDlg::OnButtonEdit() 
{
	// TODO: Add your control notification handler code here
	if(selectName == "") {
		MessageBox("未选择项！");
		return;
	}

	CAddTypeDlg dlg;
	dlg.isEdit = 1;
	dlg.m_Name = selectName;
	if (dlg.DoModal() == IDOK) {
		UpdateList();	
	}
}

void CTypesEditDlg::UpdateList()
{
	m_List.ResetContent();

	for(int i = 0; i < all_types.size(); ++i){   
		m_List.AddString(all_types[i]->name);
	}
	m_List.SetCurSel(selectIndex);
	UpdateData(false);
	OnSelchangeListTypes();

	if(all_types.size() == 0) {
		MessageBox("列表为空！");
	}
}

void CTypesEditDlg::OnSelchangeListTypes() 
{
	// TODO: Add your control notification handler code here
	selectIndex = m_List.GetCurSel();
	if(selectIndex != -1) m_List.GetText (selectIndex, selectName);
	else selectName = "";
}

BOOL CTypesEditDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
