// Graph.cpp: implementation of the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphic.h"
#include "Graph.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraph::CGraph()
{

}

CGraph::CGraph(UINT m_nDrawType,CPoint m_ptrOrigin,CPoint m_ptEnd,COLORREF m_clr)
{
	this->m_nDrawType=m_nDrawType;
	this->m_ptrOrigin=m_ptrOrigin;
	this->m_ptEnd=m_ptEnd;
	this->m_clr=m_clr;

}

CGraph::~CGraph()
{

}
