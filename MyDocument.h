#if !defined(AFX_MYDOCUMENT_H__7FE1B081_309E_4641_AF54_AFE638D90186__INCLUDED_)
#define AFX_MYDOCUMENT_H__7FE1B081_309E_4641_AF54_AFE638D90186__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDocument.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyDocument document

class MyDocument : public CDocument
{
protected:
	MyDocument();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(MyDocument)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyDocument)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MyDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(MyDocument)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDOCUMENT_H__7FE1B081_309E_4641_AF54_AFE638D90186__INCLUDED_)
