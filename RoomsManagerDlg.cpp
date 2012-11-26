// RoomsManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomsManager.h"
#include "RoomsManagerDlg.h"
#include "RoomsEditDlg.h"
#include "TypesEditDlg.h"
#include "UseRoomDlg.h"
#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MY_BUTTON_ID0 10000
vector<RoomType*> all_types;
vector<Room*> all_rooms;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomsManagerDlg dialog


CRoomsManagerDlg::CRoomsManagerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CRoomsManagerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoomsManagerDlg)
 		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRoomsManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoomsManagerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRoomsManagerDlg, CDialog)
	//{{AFX_MSG_MAP(CRoomsManagerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MANAGE_ROOMS, OnButtonManageRooms)
	ON_BN_CLICKED(IDC_BUTTON_MANAGE_TYPES, OnButtonManageTypes)
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, MY_BUTTON_ID0, MY_BUTTON_ID0 + 200, OnRoomButtonClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoomsManagerDlg message handlers

BOOL CRoomsManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	ifstream fin;
	fin.open("types.txt");
	CString line;
	RoomType *type;
	char flag = -1;
	char str[1024];
	while(fin.getline(str,1024)) {
		line = str;
		if (line == "#name") {
			type = new RoomType;
			flag = 0;
			continue;
		} else if (line == "#charge") {
			flag = 1;
			continue;
		} else if (line == "#discribe") {
			flag = 2;
			continue;
		} else if (line == "#color") {
			flag = 3;
			continue;
		} else if (line == "#END") {
			all_types.push_back(type);
			flag = -1;
			continue;
		}

		switch (flag) {
		case 0:
			type->name += line;
			break;
		case 1:
			type->charge = atoi(line);
			break;
		case 2:
			type->discribe += line;
			break;
		case 3:
			type->color = atoi(line);
			break;
		}
	}

	fin.close();

	ifstream fin2;
	fin2.open("rooms.txt");
	Room *p_room;
	flag = -1;
	while(fin2.getline(str,1024)) {
		line = str;
		if (line == "#name") {
			p_room = new Room;
			flag = 0;
			continue;
		} else if (line == "#type_name") {
			flag = 1;
			continue;
		} else if (line == "#charge") {
			flag = 2;
			continue;
		} else if (line == "#discribe") {
			flag = 3;
			continue;
		} else if (line == "#user_count") {
			flag = 4;
			continue;
		} else if (line == "#user_name") {
			flag = 5;
			continue;
		} else if (line == "#user_id") {
			flag = 6;
			continue;
		} else if (line == "#note") {
			flag = 7;
			continue;
		} else if (line == "#user_prepay") {
			flag = 8;
			continue;
		} else if (line == "#use_time") {
			flag = 9;
			continue;
		} else if (line == "#END") {
			all_rooms.push_back(p_room);
			flag = -1;
			continue;
		}

		switch (flag) {
		case 0:
			p_room->name += line;
			break;
		case 1:
			p_room->type_name += line;
			break;
		case 2:
			p_room->charge = atoi(line);
			break;
		case 3:
			p_room->discribe += line;
			break;
		case 4:
			p_room->user_count = atoi(line);
			break;
		case 5:
			p_room->user_name += line;
			break;
		case 6:
			p_room->user_id += line;
			break;
		case 7:
			p_room->note += line;
			break;
		case 8:
			p_room->user_prepay = atoi(line);
			break;
		case 9:
			p_room->use_time += line;
			break;
		}
	}

	m_Color = RGB(128, 128, 128);
	cBrush.CreateSolidBrush(m_Color);

	UpdateRoomsDisplay();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CRoomsManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CRoomsManagerDlg::OnDestroy()
{
	ofstream fout("types.txt");
	for(int i = 0; i < all_types.size(); ++i){
		RoomType *type = all_types[i];
		fout<<"#name\n"<<(LPCTSTR)type->name<<"\n#charge\n"<<type->charge<<"\n#discribe\n"<<(LPCTSTR)type->discribe<<"\n#color\n"<<type->color<<"\n#END\n\n";
		delete type;
	}
	all_types.clear();
	fout.close();
	fout.clear();

	fout.open("rooms.txt");
	for(i = 0; i < all_rooms.size(); ++i){
		Room *room = all_rooms[i];
		fout<<"#name\n"<<(LPCTSTR)room->name<<"\n#type_name\n"<<(LPCTSTR)room->type_name<<"\n#charge\n"<<room->charge<<"\n#discribe\n"<<(LPCTSTR)room->discribe
			<<"\n#user_count\n"<<room->user_count<<"\n#user_name\n"<<(LPCTSTR)room->user_name<<"\n#user_id\n"<<(LPCTSTR)room->user_id<<"\n#note\n"<<(LPCTSTR)room->note<<"\n#user_prepay\n"<<room->user_prepay
			<<"\n#use_time\n"<<(LPCTSTR)room->use_time<<"\n#END\n\n";
		delete room;
	}
	all_rooms.clear();
	fout.close();

	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRoomsManagerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRoomsManagerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRoomsManagerDlg::OnButtonManageRooms() 
{
	// TODO: Add your control notification handler code here
	CRoomsEditDlg dlg;
	dlg.DoModal();
	UpdateRoomsDisplay();
}

void CRoomsManagerDlg::OnButtonManageTypes() 
{
	// TODO: Add your control notification handler code here
	CTypesEditDlg dlg;
	dlg.DoModal();
	UpdateRoomsDisplay();
}

HBRUSH CRoomsManagerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	int index = pWnd->GetDlgCtrlID() - MY_BUTTON_ID0;
	if (index >= 0 && index <= all_rooms.size()) {
		for(int i = 0; i < all_types.size(); i++) {
			if (all_types[i]->name == all_rooms[index]->type_name) {
				m_Color = all_types[i]->color;
				break;
			}
		}
		pDC->SetBkMode(TRANSPARENT);
		cBrush.DeleteObject();
 		cBrush.CreateSolidBrush(m_Color); 
		return (HBRUSH)cBrush;
	}

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CRoomsManagerDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl >= MY_BUTTON_ID0 && nIDCtl <= MY_BUTTON_ID0 + all_rooms.size()) {
		CDC dc;
		RECT rect;
		dc.Attach(lpDrawItemStruct->hDC);   // Get the Button DC to CDC
   
		rect = lpDrawItemStruct->rcItem;     //Store the Button rect to our local rect.

		dc.Draw3dRect(&rect,GetSysColor(COLOR_BTNHIGHLIGHT),GetSysColor(COLOR_BTNSHADOW));

		CString title;
		GetDlgItemText(nIDCtl, title);
		dc.DrawText(title, &rect, DT_CENTER | DT_EDITCONTROL | DT_WORDBREAK); //Redraw the Caption of Button Window
	}
	else CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CRoomsManagerDlg::OnRoomButtonClicked(UINT nID)
{
	CUseRoomDlg dlg;
	dlg.roomIndex = nID - MY_BUTTON_ID0;
	if(dlg.DoModal() == IDOK) {
		UpdateRoomsDisplay();
	}
}

void CRoomsManagerDlg::UpdateRoomsDisplay()
{
	for (int j = 0; j < 100; ++j) {
		CWnd *pButton = GetDlgItem(MY_BUTTON_ID0 + j);
		if (pButton) {
			pButton->DestroyWindow();
			delete pButton;
			pButton = NULL;
		}
	}

	// add rooms
	// (x, y) (80,40)
	int beginX = 48*2, beginY = 80*2, width = 48*2, height = 48*2, space = 20*2;
	for (int i = 0; i < all_rooms.size(); ++i) {
		Room * room = all_rooms[i];
		CString title = room->name + "\n<" + room->type_name + ">";
		if (room->user_count > 0) title += "\n^^^^^^^^^^^\n已经住人";
		int y = i / 7, x = i % 7;
		CButton *pNewButton = new CButton;;
		pNewButton->Create(title, 
			WS_CHILD|WS_VISIBLE|BS_CENTER|BS_TOP|BS_MULTILINE|BS_PUSHBUTTON|BS_OWNERDRAW, 
			CRect(beginX + x * (width + space), beginY + y * (height + space), beginX + x * (width + space) + width, beginY + y * (height + space) + height), 
			this, MY_BUTTON_ID0 + i);
	}
}

void CRoomsManagerDlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	CString help_content = "本客房管理软件使用说明：\n";
	help_content += "1: 点击“房类管理”按钮可以添加、删除、修改房间类型；在添加房间之前需要先添加房间类型。\n";
	help_content += "2: 点击“房间管理”按钮可以添加、删除、修改房间。\n";
	help_content += "3: “房间一览表”下的方块代表房间，单击可以填入住户信息。\n";
	help_content += "4: “打印收条”按钮将会打印当前房间所显示的入住信息。打印内容包括备注信息，请将想要打印的内容填写在备注中。备注内容默认为“房间描述”，而房间描述的默认内容为“房类描述”。\n";

	help_content += "\n如有问题可联系：shengbinmeng@gmail.com";
	MessageBox(help_content);
}
