// CAD_Bezier.h : main header file for the CAD_BEZIER application
//

#if !defined(AFX_CAD_BEZIER_H__5C2A72E7_DE5F_4680_8247_2433522D09EC__INCLUDED_)
#define AFX_CAD_BEZIER_H__5C2A72E7_DE5F_4680_8247_2433522D09EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierApp:
// See CAD_Bezier.cpp for the implementation of this class
//

class CCAD_BezierApp : public CWinApp
{
public:
	CCAD_BezierApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAD_BezierApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCAD_BezierApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAD_BEZIER_H__5C2A72E7_DE5F_4680_8247_2433522D09EC__INCLUDED_)
