// Graph.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__136C22DE_1E1B_42D5_B7AE_2CEA527B8FA5__INCLUDED_)
#define AFX_GRAPH_H__136C22DE_1E1B_42D5_B7AE_2CEA527B8FA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGraph  
{
public:
	COLORREF m_clr;
	CPoint m_ptrOrigin;
	CPoint m_ptEnd;
	UINT m_nDrawType;
	CGraph();
	CGraph(UINT m_nDrawType,CPoint m_ptrOrigin,CPoint m_ptEnd,COLORREF m_clr);
	virtual ~CGraph();

};

#endif // !defined(AFX_GRAPH_H__136C22DE_1E1B_42D5_B7AE_2CEA527B8FA5__INCLUDED_)
