// EventControlView.h : interface of the CEventControlView class
//


#pragma once


class CEventControlView : public CView
{
protected: // create from serialization only
	CEventControlView();
	DECLARE_DYNCREATE(CEventControlView)

// Attributes
public:
	CEventControlDoc* GetDocument() const;

// Operations
public:
  afx_msg LRESULT OnTray( WPARAM wParam, LPARAM lParam ); 

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CEventControlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in EventControlView.cpp
inline CEventControlDoc* CEventControlView::GetDocument() const
   { return reinterpret_cast<CEventControlDoc*>(m_pDocument); }
#endif

