// EventControlDoc.h : interface of the CEventControlDoc class
//


#pragma once


class CEventControlDoc : public CDocument
{
protected: // create from serialization only
	CEventControlDoc();
	DECLARE_DYNCREATE(CEventControlDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CEventControlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


