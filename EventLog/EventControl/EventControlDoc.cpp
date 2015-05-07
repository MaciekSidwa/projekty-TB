// EventControlDoc.cpp : implementation of the CEventControlDoc class
//

#include "stdafx.h"
#include "EventControl.h"

#include "EventControlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEventControlDoc

IMPLEMENT_DYNCREATE(CEventControlDoc, CDocument)

BEGIN_MESSAGE_MAP(CEventControlDoc, CDocument)
END_MESSAGE_MAP()


// CEventControlDoc construction/destruction

CEventControlDoc::CEventControlDoc()
{
	// TODO: add one-time construction code here

}

CEventControlDoc::~CEventControlDoc()
{
}

BOOL CEventControlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEventControlDoc serialization

void CEventControlDoc::Serialize(CArchive& ar)
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


// CEventControlDoc diagnostics

#ifdef _DEBUG
void CEventControlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEventControlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEventControlDoc commands
