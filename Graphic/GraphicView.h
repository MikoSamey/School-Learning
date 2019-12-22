// GraphicView.h : interface of the CGraphicView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHICVIEW_H__A1506F3C_F936_4CDB_8D4D_945E3BA507FA__INCLUDED_)
#define AFX_GRAPHICVIEW_H__A1506F3C_F936_4CDB_8D4D_945E3BA507FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphicView : public CScrollView
{
protected: // create from serialization only
	CGraphicView();
	DECLARE_DYNCREATE(CGraphicView)

// Attributes
public:
	CGraphicDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphicView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphicView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphicView)
	afx_msg void OnDot();
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnFileSave();
	afx_msg void OnFileOpen();
	afx_msg void OnSetting();
	afx_msg void OnColor();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_startDraw;
	
	//CFont m_font;
	COLORREF m_clr;
	int m_nLineStyle;
	UINT m_nLineWidth;
	
	CDC m_dcCompatible;
	CMetaFileDC m_dcMetaFile;
	CPtrArray m_ptrArray;

	CPoint m_ptOrigin;
	CPoint m_ptOld;
	UINT m_nDrawType;
	HCURSOR m_HCross;/*…Ë÷√π‚±Í*/
};

#ifndef _DEBUG  // debug version in GraphicView.cpp
inline CGraphicDoc* CGraphicView::GetDocument()
   { return (CGraphicDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHICVIEW_H__A1506F3C_F936_4CDB_8D4D_945E3BA507FA__INCLUDED_)
