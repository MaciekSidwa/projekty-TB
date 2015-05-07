// EventControl.h : main header file for the EventControl application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CEventControlApp:
// See EventControl.cpp for the implementation of this class
//

class CEventControlApp : public CWinApp
{
public:
	CEventControlApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CEventControlApp theApp;