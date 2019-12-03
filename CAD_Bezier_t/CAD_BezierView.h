// CAD_BezierView.h : interface of the CCAD_BezierView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAD_BEZIERVIEW_H__7AD246D7_3699_4922_BFB7_7D9764D06BF3__INCLUDED_)
#define AFX_CAD_BEZIERVIEW_H__7AD246D7_3699_4922_BFB7_7D9764D06BF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define N_MAX_POINT 10	//���Ŀ��Ƶ���Ŀ

class CCAD_BezierView : public CView
{
protected: // create from serialization only
	CCAD_BezierView();
	DECLARE_DYNCREATE(CCAD_BezierView)

// Attributes
public:
	CCAD_BezierDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCAD_BezierView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawCtrPloygon(CDC *pDC);		//���ƿ��ƶ����
	void DrawBezier(CDC *pDC);//����Bezier��
	long DeCasteliau(double t,long *p);//�¿�˹������㷨������Bezier�����ϵĵ㣩
	virtual ~CCAD_BezierView();

public:
	void DrawHermite(CDC *pDC);
	bool m_bDrawStruct;
	bool m_AbleToLeftBtn;
	int m_i;				//�ƶ����õ������±�
	bool m_AbleToMove;		//�ж��Ƿ�����ƶ�
	void DrawBSplineStruct(CDC *pDC);
	void ClearMemory();
	void B3Curves(CPoint p[],CDC *pDC);
	int m_iDrawType;//�����������͵��ж�����
	bool m_bFlag;	//�����ж�����

	double *p;		//���Ƶ����(��ȷ������<=10)

	int CtrlPNum;	//���Ƶ���Ŀ<=10
	CPoint *pt;		//���Ƶ�����

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCAD_BezierView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBezierAlg();
	afx_msg void OnBsplineAlg();
	afx_msg void OnMenuStruct();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMenuClear();
	afx_msg void OnMenuHermite();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CAD_BezierView.cpp
inline CCAD_BezierDoc* CCAD_BezierView::GetDocument()
   { return (CCAD_BezierDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAD_BEZIERVIEW_H__7AD246D7_3699_4922_BFB7_7D9764D06BF3__INCLUDED_)
