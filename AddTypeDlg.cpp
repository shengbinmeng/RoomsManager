// AddTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomsManager.h"
#include "AddTypeDlg.h"
#include "AddRoomDlg.h"
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	vector<RoomType*> all_types;
extern	vector<Room*> all_rooms;

/////////////////////////////////////////////////////////////////////////////
// CAddTypeDlg dialog


CAddTypeDlg::CAddTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddTypeDlg)
	m_Charge = 0;
	m_Discribe = _T("");
	m_Name = _T("");
	//}}AFX_DATA_INIT

	isEdit = 0;
	editPosition = -1;
	m_Color = RGB(128,128,128);
}


void CAddTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddTypeDlg)
	DDX_Text(pDX, IDC_EDIT_CHARGE, m_Charge);
	DDX_Text(pDX, IDC_EDIT_DISCRIBR, m_Discribe);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CAddTypeDlg)
	ON_BN_CLICKED(IDC_STATIC_COLOR, OnStaticColor)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddTypeDlg message handlers

BOOL CAddTypeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	if(isEdit) {
		for (int i = 0; i < all_types.size(); ++i){
			if (all_types[i]->name == m_Name) {
				m_Charge = all_types[i]->charge;
				m_Discribe = all_types[i]->discribe;
				m_Color = all_types[i]->color;
				editPosition = i;
				break;
			}
		}
	}

	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CAddTypeDlg::OnOK() 
{
	// TODO: Add extra validation here

	UpdateData(TRUE);

	if((m_Name == "") || (m_Charge == -1) || (m_Discribe == "")) {
		MessageBox("请输入完整的信息！");
		return ;
	}

	for(int i = 0; i < all_types.size(); ++i) {
		if(all_types[i]->name == m_Name) {
			if (isEdit && i == editPosition) continue;
			else break;
		}
	}
	if(i < all_types.size()) {
		MessageBox("此名称已存在!");
		return ;
	}
	else
	{
		if (isEdit) {
			RoomType *type = all_types[editPosition];
			if (type->name != m_Name) {
				CString str = "";
				for (int i = 0; i < all_rooms.size(); ++i) {
					if (all_rooms[i]->type_name == type->name) {
						str += "(" + all_rooms[i]->name + ") ";
						all_rooms[i]->type_name = m_Name;
					}
				}
				if (str != "") {
					MessageBox("您改变了类型名称。该类型中包含以下房间： " + str +" ，它们的类型名也已经更新。",NULL,MB_ICONINFORMATION|MB_OK|MB_DEFBUTTON2);
				}
			}
			type->name = m_Name;
			type->charge = m_Charge;
			type->discribe = m_Discribe;
			type->color = m_Color;

		} else {
			RoomType *type = new RoomType;
			type->name = m_Name;
			type->charge = m_Charge;
			type->discribe = m_Discribe;
			type->color = m_Color;
			all_types.push_back(type);
		}

		CDialog::OnOK();
	}
}

 void CAddTypeDlg::OnStaticColor()
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;  
	dlg.m_cc.Flags |= CC_FULLOPEN | CC_RGBINIT;
	dlg.m_cc.rgbResult = m_Color;
	if(dlg.DoModal() == IDOK)   
	{
 		m_Color = dlg.GetColor();  
	}
	Invalidate(true);
}

HBRUSH CAddTypeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_COLOR) {
		cBrush.DeleteObject();
 		cBrush.CreateSolidBrush(m_Color); 
		return (HBRUSH)cBrush;
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
