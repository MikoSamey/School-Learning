// CAD_BezierDoc.cpp : implementation of the CCAD_BezierDoc class
//

#include "stdafx.h"
#include "CAD_Bezier.h"

#include "CAD_BezierDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierDoc

IMPLEMENT_DYNCREATE(CCAD_BezierDoc, CDocument)

BEGIN_MESSAGE_MAP(CCAD_BezierDoc, CDocument)
	//{{AFX_MSG_MAP(CCAD_BezierDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierDoc construction/destruction

CCAD_BezierDoc::CCAD_BezierDoc()
{
	// TODO: add one-time construction code here

}

CCAD_BezierDoc::~CCAD_BezierDoc()
{
}

BOOL CCAD_BezierDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierDoc serialization

void CCAD_BezierDoc::Serialize(CArchive& ar)
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
// CCAD_BezierDoc diagnostics

#ifdef _DEBUG
void CCAD_BezierDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCAD_BezierDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierDoc commands
