
// Aircraft Stability Analysis.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CAircraftStabilityAnalysisApp:
// See Aircraft Stability Analysis.cpp for the implementation of this class
//

class CAircraftStabilityAnalysisApp : public CWinApp
{
public:
	CAircraftStabilityAnalysisApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CAircraftStabilityAnalysisApp theApp;