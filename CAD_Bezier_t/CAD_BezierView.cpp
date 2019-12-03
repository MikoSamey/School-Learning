// CAD_BezierView.cpp : implementation of the CCAD_BezierView class
//

#include "stdafx.h"
#include "CAD_Bezier.h"

#include "CAD_BezierDoc.h"
#include "CAD_BezierView.h"

#include <math.h>
#define N_MAX_POINT 10	//最大的控制点数目
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierView

IMPLEMENT_DYNCREATE(CCAD_BezierView, CView)

BEGIN_MESSAGE_MAP(CCAD_BezierView, CView)
	//{{AFX_MSG_MAP(CCAD_BezierView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_BEZIER_ALG, OnBezierAlg)
	ON_COMMAND(IDM_BSPLINE_ALG, OnBsplineAlg)
	ON_COMMAND(ID_MENU_STRUCT, OnMenuStruct)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_MENU_CLEAR, OnMenuClear)
	ON_COMMAND(ID_MENU_HERMITE, OnMenuHermite)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierView construction/destruction

CCAD_BezierView::CCAD_BezierView()
{
	// TODO: add construction code here
	m_bFlag = 1;			//可以绘制控制点
	pt=new CPoint[N_MAX_POINT];
	p = new double[N_MAX_POINT];
	CtrlPNum = 0;
	m_iDrawType = -1;		//未选择绘制方式
	m_bDrawStruct = FALSE;	//不能绘制b样条结构图
	m_i = -1;
}

CCAD_BezierView::~CCAD_BezierView()
{
}

BOOL CCAD_BezierView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierView drawing

void CCAD_BezierView::OnDraw(CDC* pDC)
{
	CCAD_BezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	/*
	* 双缓冲绘制控制点以及相应的曲线
	*/
	CRect rect;
	GetClientRect(&rect);//获得客户区的大小
////////////////
	CDC memDC;//内存DC
	CBitmap NewBitmap,*pOldBitmap;	//内存中承载图像的临时位图
	memDC.CreateCompatibleDC(pDC);	//建立与屏幕pDC兼容的memDC
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//创建兼容位图---客户区大小，pDC设备

	pOldBitmap = memDC.SelectObject(&NewBitmap);	//将兼容位图选入memDC
	memDC.FillSolidRect(rect,pDC->GetBkColor());	//按原来背景填充客户区，否则是黑色

    memDC.BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);

	DrawCtrPloygon(&memDC);
	switch(m_iDrawType)
	{
	case -1:
		//提示信息的对话框
		MessageBox("请使用鼠标左键选取控制点，右键控制点移动\n\n\t点击菜单选项绘制相应曲线","提示",MB_OK);
		m_iDrawType = -2;
		break;
	case 0:
		memDC.TextOut(50,50,"绘制Bezier曲线：");
		DrawBezier(&memDC);
		break;
	case 1:
		memDC.TextOut(50,50,"绘制B样条曲线：");
		B3Curves(pt,&memDC);
		if(m_bDrawStruct)
		{
			DrawBSplineStruct(&memDC);
		}
		break;
	case 3:
		memDC.TextOut(50,50,"绘制Hermite曲线：");
		if(CtrlPNum >= 4)
		{
			DrawHermite(&memDC);
		}
		break;
	default:
		break;
	}

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);

	memDC.SelectObject(pOldBitmap);	//恢复位图
	NewBitmap.DeleteObject();	//删除位图
	memDC.DeleteDC();			//删除memDC

}

/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierView printing

BOOL CCAD_BezierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCAD_BezierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCAD_BezierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierView diagnostics

#ifdef _DEBUG
void CCAD_BezierView::AssertValid() const
{
	CView::AssertValid();
}

void CCAD_BezierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCAD_BezierDoc* CCAD_BezierView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCAD_BezierDoc)));
	return (CCAD_BezierDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCAD_BezierView message handlers

/*绘制Hermite曲线*/
void CCAD_BezierView::DrawHermite(CDC *pDC)
{
	if(CtrlPNum < 4) //如果不足4个控制点
		return;	//返回，无法绘制

	CPoint p0,p1,p0_tg,p1_tg; //起点终点，以及构成切向量的2个点

	p0 = pt[0];p1 = pt[2];
	
	p0_tg.x = pt[1].x - pt[0].x;
	p0_tg.y = pt[1].y - pt[0].y;

	p1_tg.x = pt[3].x - pt[2].x;
	p1_tg.y = pt[3].y - pt[2].y;

	double delt = 1.0/1000;	//步长,将控制点的距离划分成1000等分
	CPoint p;//曲线上的点
	for(double t=0;t<=1;t+=delt)
	{
		p.x = long(p0.x * (1-3*pow(t,2)+2*pow(t,3)) +
				p1.x * (3*pow(t,2)-2*pow(t,3))+
				p0_tg.x * (t-2*pow(t,2)+pow(t,3))+
				p1_tg.x * (-pow(t,2)+pow(t,3)));

		p.y = long(p0.y * (1-3*pow(t,2)+2*pow(t,3)) +
				p1.y * (3*pow(t,2)-2*pow(t,3))+
				p0_tg.y * (t-2*pow(t,2)+pow(t,3))+
				p1_tg.y * (-pow(t,2)+pow(t,3)));
		pDC->SetPixel(p.x,p.y,RGB(128,0,255));
	}

}

/*绘制二维曲线时，德卡斯特里奥函数被调用两次*/
long CCAD_BezierView::DeCasteliau(double t, long *p)
{
	double P[N_MAX_POINT][N_MAX_POINT];
	int n = CtrlPNum-1;	
	for(int k = 0;k<=n;k++)
	{
		P[0][k] = p[k];	//p[]里存放的是点的坐标分量（x轴、y轴）
	}
	for(int r = 1;r<=n;r++)
	{
		for(int i = 0;i<=n-r;i++)
		{
			P[r][i] = (1-t)*P[r-1][i] + t*P[r-1][i+1];
		}
	}
	return (long(P[n][0]));
}

/*绘制Bezier曲线*/
void CCAD_BezierView::DrawBezier(CDC *pDC)
{
	double delt = 1.0/5000;	//步长,将控制点的距离划分成5000等分
	int n = CtrlPNum-1;
	CPoint p;
	long px[N_MAX_POINT],py[N_MAX_POINT];
	for(int k = 0;k<=n;k++)
	{
		px[k] = pt[k].x;
		py[k] = pt[k].y;
	}
	for(double t=0;t<=1;t+=delt)
	{
		p.x = DeCasteliau(t, px);//x方向
		p.y = DeCasteliau(t, py);//y方向
		pDC->SetPixel(p.x,p.y,RGB(255,0,255));
	}

}

/*绘制B样条曲线*/
void CCAD_BezierView::B3Curves(CPoint p[], CDC *pDC)
{
	double delt = 1.0/10;
	CPoint PStart,PEnd;			//每段B样条曲线的起点和终点
	double F03,F13,F23,F33;		//B样条基函数

	PStart.x = long((pt[0].x+4.0*pt[1].x+pt[2].x)/6.0);	//t = 0的起点x坐标
	PStart.y = long((pt[0].y+4.0*pt[1].y+pt[2].y)/6.0); //t = 0的起点y坐标
	pDC->MoveTo(PStart);

	CPen NewPen1(PS_SOLID,2,RGB(255,0,0));
	CPen *OldPen1=pDC->SelectObject(&NewPen1);

	for(int i=1;i <= CtrlPNum-3;i++)	//4个控制点决定一段B样条曲线
	{
		for(double t=0;t<=1;t+=delt)
		{
			F03 = (-t*t*t+3*t*t-3*t+1)/6;//计算F0,3(t)
			F13 = (3*t*t*t-6*t*t+4)/6;//计算F1,3(t)
			F23 = (-3*t*t*t+3*t*t+3*t+1)/6;//计算F2,3(t)
			F33 = t*t*t/6;//计算B3,3(t)

			PEnd.x = long(pt[i-1].x*F03+pt[i].x*F13+pt[i+1].x*F23+pt[i+2].x*F33);
			PEnd.y = long(pt[i-1].y*F03+pt[i].y*F13+pt[i+1].y*F23+pt[i+2].y*F33);
			pDC->LineTo(PEnd);
		}
	}
	pDC->SelectObject(OldPen1);
	NewPen1.DeleteObject();	

}

/*绘制B样条几何结构*/
void CCAD_BezierView::DrawBSplineStruct(CDC *pDC)
{

	CPen NewPen(PS_DOT,1,RGB(128,128,128));
	CPen *OldPen=pDC->SelectObject(&NewPen);
	int x,y;
	for(int i=1;i<=CtrlPNum-2;i++)
	{
		x=(pt[i-1].x+pt[i+1].x)/2;
		y=(pt[i-1].y+pt[i+1].y)/2;

		pDC->MoveTo(pt[i].x,pt[i].y);
		pDC->LineTo(x,y);

		pDC->MoveTo(pt[i-1].x,pt[i-1].y);
		pDC->LineTo(pt[i+1].x,pt[i+1].y);
	}
	pDC->SelectObject(OldPen);
	NewPen.DeleteObject();	

}

/*绘制控制点多边形*/
void CCAD_BezierView::DrawCtrPloygon(CDC *pDC)
{	
	CPen NewPen, *pOldPen;					//宽度2的黑笔
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));
	pOldPen = pDC->SelectObject(&NewPen);

	CBrush NewBrush, *pOldBrush;			//实心黑刷子
	NewBrush.CreateSolidBrush(RGB(0,0,0));
	pOldBrush = pDC->SelectObject(&NewBrush);

	if(m_iDrawType != 3) //非Hermite曲线
	{
	for(int i = 0;i<CtrlPNum;i++)
	{
		if(0 == i) //针对第一个点
		{
			pDC->MoveTo(pt[i].x,pt[i].y);
			pDC->Ellipse(pt[i].x-4,pt[i].y-4,pt[i].x+4,pt[i].y+4); //半径为1的实心圆，表示控制点
		}
		else
		{
			pDC->LineTo(pt[i]);
			pDC->Ellipse(pt[i].x-4,pt[i].y-2,pt[i].x+4,pt[i].y+4);
		}
	}
	}
	else
	{
		pDC->MoveTo(pt[0]);
		pDC->LineTo(pt[1]);

		pDC->MoveTo(pt[2]);
		pDC->LineTo(pt[3]);

		for(int i = 0;i<4;i++)
		{
			pDC->Ellipse(pt[i].x-4,pt[i].y-2,pt[i].x+4,pt[i].y+4);
		}
	}
	//处理后事
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

}


////////////////////////////鼠标响应函数////////////////////////////

/*
* 单击鼠标左键
* 鼠标位置点 = 控制点 ； 同时调用 DrawCtrPolygon() 函数绘制控制多边形
*/
void CCAD_BezierView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bFlag)	//可以绘图
	{
		pt[CtrlPNum] = point;
		if(CtrlPNum < N_MAX_POINT)
		{
			CtrlPNum++;
		}
		else
		{
			m_bFlag = FALSE;	//超过最大值就不再绘制了
		}
	}

	Invalidate(FALSE);

	CView::OnLButtonDown(nFlags, point);
}

/*点击鼠标右键绘制曲线*/
void CCAD_BezierView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bFlag = FALSE;

	if (TRUE == m_AbleToLeftBtn)//鼠标位于控制点附近
	{
		m_AbleToMove = TRUE;//鼠标按下，开始移动
	}
	
	CView::OnRButtonDown(nFlags, point);
}

void CCAD_BezierView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonUp(nFlags, point);
}

void CCAD_BezierView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_AbleToMove = FALSE;//停止移动，重绘
	Invalidate(FALSE);
	CView::OnRButtonUp(nFlags, point);
}

/*移动鼠标时状态栏显示鼠标位置坐标值*/
void CCAD_BezierView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString strx,stry;
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;

	CStatusBar *pStatus = &pFrame->m_wndStatusBar;

	if(pStatus)
	{
		strx.Format("x=%d",point.x);
		stry.Format("y=%d",point.y);

		CClientDC dc(this);
		CSize sizex = dc.GetTextExtent(strx);
		CSize sizey = dc.GetTextExtent(stry);

		pStatus->SetPaneInfo(1,ID_INDICATOR_X,SBPS_NORMAL,sizex.cx);
		pStatus->SetPaneText(1,strx);

		pStatus->SetPaneInfo(2,ID_INDICATOR_Y,SBPS_NORMAL,sizey.cx);
		pStatus->SetPaneText(2,stry);
	}

	if(TRUE == m_AbleToMove)
	{
		pt[m_i] = point;
	}
	m_i = -1;	//默认-1
	
	for(int i = 0;i<CtrlPNum;i++)
	{
		if((point.x - pt[i].x)*(point.x - pt[i].x) + (point.y - pt[i].y)*(point.y - pt[i].y) < 25)
		{
			m_i = i;
			m_AbleToLeftBtn = TRUE;
			break;
		}
	}
	if(N_MAX_POINT == i)
	{
		m_i = -1;
	}
	Invalidate(FALSE);

	CView::OnMouseMove(nFlags, point);
}


////////////////菜单相应函数---选择绘制曲线//////////////

void CCAD_BezierView::OnMenuHermite() //Hermite曲线
{
	// TODO: Add your command handler code here
	m_iDrawType = 3;
	Invalidate(FALSE);
}

void CCAD_BezierView::OnBezierAlg() //Bezier曲线
{
	// TODO: Add your command handler code here
	//ClearMemory();
	m_iDrawType = 0;
	Invalidate(FALSE);
}

void CCAD_BezierView::OnBsplineAlg() //B样条曲线
{
	// TODO: Add your command handler code here
	//ClearMemory();
	m_iDrawType = 1;
	Invalidate(FALSE);
}

/*B样条曲线的几何结构*/
void CCAD_BezierView::OnMenuStruct() 
{
	// TODO: Add your command handler code here
	m_bDrawStruct = TRUE;
	Invalidate(FALSE);
}

//////////////////////////////////////////////
/*清理成员变量*/
void CCAD_BezierView::ClearMemory()
{
	//RedrawWindow();
	if(pt != 0)
	{
		delete pt;
		pt=new CPoint[N_MAX_POINT];
	}
	CtrlPNum = 0;
	m_bFlag = TRUE;			//可以读入控制点
	m_iDrawType = -2;		//未选择绘制方式
	m_bDrawStruct = FALSE;	//不能绘制b样条结构图
	m_i = -1;				//不能修改控制点
}

void CCAD_BezierView::OnMenuClear() 
{
	// TODO: Add your command handler code here
	ClearMemory();
	Invalidate(FALSE);
}

