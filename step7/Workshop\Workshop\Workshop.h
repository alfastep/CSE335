
// Workshop.h : main header file for the Workshop application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CWorkshopApp:
// See Workshop.cpp for the implementation of this class
//

/**
* Constructor for WorkshopApp
*/
class CWorkshopApp : public CWinApp
{
public:
	CWorkshopApp();


// Overrides
public:
	/// Initial Instance
	virtual BOOL InitInstance();
	
	/**
	* Instance for exiting
	*
	* \returns int as value
	*/
	virtual int ExitInstance();

// Implementation

public:
	

	/// App command to run the dialog
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


private:
	///Variable for handling Start Input
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    /// Gdiplus token
	ULONG_PTR gdiplusToken;
};

extern CWorkshopApp theApp;
