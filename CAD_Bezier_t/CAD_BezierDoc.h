// CAD_BezierDoc.h : interface of the CCAD_BezierDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAD_BEZIERDOC_H__CFCAE3C0_2F0F_417E_B28C_8BC3AACC3A96__INCLUDED_)
#define AFX_CAD_BEZIERDOC_H__CFCAE3C0_2F0F_417E_B28C_8BC3AACC3A96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCAD_BezierDoc : public CDocument
{
protected: // create from serialization only
	CCAD_BezierDoc();
	DECLARE_DYNCREATE(CCAD_BezierDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAD_BezierDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCAD_BezierDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCAD_BezierDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAD_BEZIERDOC_H__CFCAE3C0_2F0F_417E_B28C_8BC3AACC3A96__INCLUDED_)
