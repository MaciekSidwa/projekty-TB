// EventControlView.cpp : implementation of the CEventControlView class
//

#include "stdafx.h"
#include "EventControl.h"

#include "EventControlDoc.h"
#include "EventControlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define MYWM_NOTIFYICON		(WM_APP+1000)

// CEventControlView

IMPLEMENT_DYNCREATE(CEventControlView, CView)

BEGIN_MESSAGE_MAP(CEventControlView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
  ON_MESSAGE(MYWM_NOTIFYICON, OnTray)

END_MESSAGE_MAP()

// CEventControlView construction/destruction

CEventControlView::CEventControlView()
{
	// TODO: add construction code here

}

CEventControlView::~CEventControlView()
{
}

BOOL CEventControlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEventControlView drawing

void CEventControlView::OnDraw(CDC* /*pDC*/)
{
	CEventControlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CEventControlView printing

BOOL CEventControlView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEventControlView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEventControlView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEventControlView diagnostics

#ifdef _DEBUG
void CEventControlView::AssertValid() const
{
	CView::AssertValid();
}

void CEventControlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEventControlDoc* CEventControlView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEventControlDoc)));
	return (CEventControlDoc*)m_pDocument;
}
#endif //_DEBUG


// CEventControlView message handlers

BOOL TrayMessage(HWND hDlg, DWORD dwMessage, UINT uID, HICON hIcon, PSTR pszTip)
{
        BOOL res;

	NOTIFYICONDATA tnd;

	tnd.cbSize		= sizeof(NOTIFYICONDATA);
	tnd.hWnd		= hDlg;
	tnd.uID			= uID;

	tnd.uFlags		= NIF_MESSAGE|NIF_ICON|NIF_TIP;
	tnd.uCallbackMessage	= MYWM_NOTIFYICON;
	tnd.hIcon		= hIcon;
	if (pszTip)
	{
		lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
	}
	else
	{
		tnd.szTip[0] = '\0';
	}

	res = Shell_NotifyIcon(dwMessage, &tnd);

	if (hIcon)
	    DestroyIcon(hIcon);

	return res;
}

//BOOL CVswdeDlg::OnTray( WPARAM wParam, LPARAM lParam ) 
LRESULT CEventControlView::OnTray( WPARAM wParam, LPARAM lParam ) 
{
	// TODO: Add your command handler code here
	//	CAboutDlg dlgAbout;
	//	dlgAbout.DoModal();
  if ( lParam == WM_LBUTTONDOWN )
    {
    ShowWindow( SW_SHOW );
	  TrayMessage(GetSafeHwnd(), NIM_DELETE, MYWM_NOTIFYICON, NULL, NULL);
  	//return (TRUE);
    }


	return 1;
	
}
