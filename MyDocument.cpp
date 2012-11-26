// MyDocument.cpp : implementation file
//

#include "stdafx.h"
#include "RoomsManager.h"
#include "MyDocument.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyDocument

IMPLEMENT_DYNCREATE(MyDocument, CDocument)

MyDocument::MyDocument()
{
}

BOOL MyDocument::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

MyDocument::~MyDocument()
{
}


BEGIN_MESSAGE_MAP(MyDocument, CDocument)
	//{{AFX_MSG_MAP(MyDocument)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyDocument diagnostics

#ifdef _DEBUG
void MyDocument::AssertValid() const
{
	CDocument::AssertValid();
}

void MyDocument::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// MyDocument serialization

void MyDocument::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// MyDocument commands
