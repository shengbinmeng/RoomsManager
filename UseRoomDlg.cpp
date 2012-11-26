// UseRoomDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoomsManager.h"
#include "UseRoomDlg.h"

extern vector<Room*> all_rooms;
extern vector<RoomType*> all_types;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUseRoomDlg dialog


CUseRoomDlg::CUseRoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUseRoomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUseRoomDlg)
	m_Note = _T("");
	m_Prepay = 0;
	m_UserID = _T("");
	m_UserName = _T("");
	m_Title = _T("");
	m_Charge = 0;
	//}}AFX_DATA_INIT
}


void CUseRoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUseRoomDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER_IN_TIME, m_InTime);
	DDX_Text(pDX, IDC_EDIT_NOTE, m_Note);
	DDX_Text(pDX, IDC_EDIT_PREPAY, m_Prepay);
	DDX_Text(pDX, IDC_EDIT_USER_ID, m_UserID);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_UserName);
	DDX_Text(pDX, IDC_STATIC_TITLE, m_Title);
	DDX_Text(pDX, IDC_EDIT_CHARGE, m_Charge);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUseRoomDlg, CDialog)
	//{{AFX_MSG_MAP(CUseRoomDlg)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseRoomDlg message handlers

BOOL CUseRoomDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	theRoom = all_rooms[roomIndex];

	m_Title = theRoom->name; 
	m_UserName = theRoom->user_name;
	m_UserID = theRoom->user_id;
	m_Charge = theRoom->charge;
	m_Prepay = theRoom->user_prepay;
	m_Note = (theRoom->note == "" ? theRoom->discribe : theRoom->note);
	if (theRoom->use_time != "") {
		COleDateTime time;
		time.ParseDateTime(theRoom->use_time);
		m_InTime.SetTime(time);
	}

	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUseRoomDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(true);

	theRoom->user_name = m_UserName;
	theRoom->user_id = m_UserID;
	theRoom->charge = m_Charge;
	theRoom->user_prepay = m_Prepay;
	theRoom->note = m_Note;
	if (m_UserName != "") {
		COleDateTime time;
		m_InTime.GetTime(time);
		theRoom->use_time = time.Format("%Y-%m-%d %H:%M:%S");
		theRoom->user_count = 1;
	} else {
		theRoom->user_count = 0;
		theRoom->use_time = "";
	}

	CDialog::OnOK();
}

void CUseRoomDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}


void CUseRoomDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	int n = MessageBox("确定要清除该房间的入住信息?", NULL, MB_ICONINFORMATION|MB_YESNO|MB_DEFBUTTON2);
	if(n == IDNO) return; 
	else {
		m_UserName = "";
		m_UserID = "";
		for (int i = 0; i < all_types.size(); ++i) {
			if(all_types[i]->name == theRoom->type_name)
			m_Charge = all_types[i]->charge;
			break;
		}
		m_Prepay = 0;
		m_Note = "";
		m_InTime.SetTime(&(CTime::GetCurrentTime())); 
	}

	UpdateData(false);
}

void CUseRoomDlg::OnButtonPrint() 
{
	// TODO: Add your control notification handler code here
	CString info = "";
	if (m_UserName == "") {
		info = "姓名为空，该房间将没有住人。";
	}
	int res = MessageBox(info + "确定要打印当前显示的信息?", NULL, MB_ICONINFORMATION|MB_YESNO|MB_DEFBUTTON2);
	if(res == IDNO) return; 

	UpdateData(true);

	PRINTDLG pd;
	pd.lStructSize = sizeof(PRINTDLG);
	pd.Flags = PD_RETURNDC;
	pd.hDC = NULL;
	pd.hwndOwner = NULL;
	pd.hInstance = NULL;
	pd.nMaxPage = 1;
	pd.nMinPage = 1;
	pd.nFromPage = 1;
	pd.nToPage = 1;
	pd.nCopies = 1;
	pd.hDevMode = NULL;
	pd.hDevNames = NULL;
	//顯示列印對話方塊，由用戶來設定紙張大小等。
	if(!PrintDlg(&pd)) return ;
	ASSERT(pd.hDC!=NULL);
	int nHorRes = GetDeviceCaps(pd.hDC, HORZRES);
	int nVerRes = GetDeviceCaps(pd.hDC, VERTRES);
	int nXMargin = 2;
	int nYMargin = 2;
	TEXTMETRIC tm;
	GetTextMetrics(pd.hDC, &tm);
	int nCharHeight = tm.tmHeight;
	int nCharWidth = tm.tmAveCharWidth;

	int nColX =nXMargin * nCharWidth;

	DOCINFO di;
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = "收条";
	di.lpszOutput = (LPTSTR) NULL;
	di.lpszDatatype = (LPTSTR) NULL;
	di.fwType = 0;
	StartDoc(pd.hDC, &di);
	StartPage(pd.hDC);

	CString printContent = "宾馆收条";
	TextOut(pd.hDC, nHorRes / 2 - 2 * nCharWidth, nCharHeight * 2, printContent, strlen(printContent));

	CString user = "";
	if(m_UserName != "") user = "住户：" + m_UserName + "    ";
	printContent.Format("%s住宿费：%d 元    押金：%d 元\r\n", user, m_Charge, m_Prepay);
	TextOut(pd.hDC, nCharWidth * 8, nCharHeight * 5, printContent, strlen(printContent));

	printContent = m_Note;
	int n = strlen(printContent);
	int line_size = nHorRes / nCharWidth - 16;
	int i = 0;
	for (; n > 0 ;) {
		if (i * line_size + line_size < n) {
			CString str = printContent.Mid(i * line_size, line_size);
			TextOut(pd.hDC, nCharWidth * 8, nCharHeight * (6 + i), str, strlen(str));
			i ++;
			continue;
		} else {
			CString str = printContent.Mid(i * line_size, n - i * line_size);
			TextOut(pd.hDC, nCharWidth * 8, nCharHeight * (6 + i), str, strlen(str));
			break;
		}
	}

	printContent = "时间：" + (CTime::GetCurrentTime()).Format("%Y-%m-%d %H:%M") + "\r\n";
	TextOut(pd.hDC, nCharWidth * 8, nCharHeight * (8 + i), printContent, strlen(printContent));

	EndPage(pd.hDC);
	EndDoc(pd.hDC);
	//列印結束
	DeleteDC(pd.hDC);
}
