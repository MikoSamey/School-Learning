// GraphicView.cpp : implementation of the CGraphicView class
//

#include "stdafx.h"
#include "Graphic.h"

#include "GraphicDoc.h"
#include "GraphicView.h"

#include "SettingDlg.h"
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphicView

IMPLEMENT_DYNCREATE(CGraphicView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphicView, CScrollView)
	//{{AFX_MSG_MAP(CGraphicView)
	ON_COMMAND(IDM_DOT, OnDot)
	ON_COMMAND(IDM_LINE, OnLine)
	ON_COMMAND(IDM_RECTANGLE, OnRectangle)
	ON_COMMAND(IDM_ELLIPSE, OnEllipse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(IDM_SETTING, OnSetting)
	ON_COMMAND(IDM_COLOR, OnColor)
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphicView construction/destruction

CGraphicView::CGraphicView()
{
	// TODO: add construction code here
	m_nDrawType=0;/*用来保存用户的选择*/
	m_ptOrigin=0;/*起点*/
	m_ptOld=0;/*旧点*/
	m_nLineWidth=0;/*线宽*/
	m_nLineStyle=0;/*线型*/

	m_startDraw=false;/*动态画线的基础，没有会连续画线*/

	/*初始化m_HCross为十字光标*/
	m_HCross=AfxGetApp()->LoadStandardCursor(IDC_CROSS);

	m_clr=RGB(255,0,0);

	m_dcMetaFile.Create();
	/*参数为NULL--新的内存元文件*/
	/*参数为文件名---新的元文件*/
}

CGraphicView::~CGraphicView()
{
}

BOOL CGraphicView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView drawing

void CGraphicView::OnDraw(CDC* pDC)
{
	CGraphicDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	/*将保存的图像取出来*/
	
	
	//CPen pen(m_nLineStyle,m_nLineWidth,m_clr);/*一个m_clr颜色的画笔*/
	//pDC->SelectObject(&pen);

	//CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//透明画刷
	//pDC->SelectObject(pBrush);

	for(int i=0;i<m_ptrArray.GetSize();i++)
	{
		m_clr=((CGraph*)m_ptrArray.GetAt(i))->m_clr;
		CPen pen(m_nLineStyle,m_nLineWidth,m_clr);/*一个m_clr颜色的画笔*/
		pDC->SelectObject(&pen);

		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//透明画刷
		pDC->SelectObject(pBrush);

		switch(((CGraph*)m_ptrArray.GetAt(i))->m_nDrawType)
		{
			
			
		case 1:
			pDC->SetPixel(((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd,m_clr);
			break;
		case 2:
			pDC->MoveTo(((CGraph*)m_ptrArray.GetAt(i))->m_ptrOrigin);
			pDC->LineTo(((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd);
			break;
		case 3:
			pDC->Rectangle(CRect(((CGraph*)m_ptrArray.GetAt(i))->m_ptrOrigin,
				((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd));
			break;
		case 4:
			pDC->Ellipse(CRect(((CGraph*)m_ptrArray.GetAt(i))->m_ptrOrigin,
				((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd));
			break;
		}
	}

	HMETAFILE hmetaFile;
	hmetaFile=m_dcMetaFile.Close();
	pDC->PlayMetaFile(hmetaFile);
	m_dcMetaFile.Create();
	m_dcMetaFile.PlayMetaFile(hmetaFile);
	DeleteMetaFile(hmetaFile);

	/*CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&m_dcCompatible,0,0,SRCCOPY);
*/
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView printing

BOOL CGraphicView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGraphicView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGraphicView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGraphicView diagnostics

#ifdef _DEBUG
void CGraphicView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphicView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphicDoc* CGraphicView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicDoc)));
	return (CGraphicDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphicView message handlers

void CGraphicView::OnDot() 
{
	// TODO: Add your command handler code here
	m_nDrawType=1;
}

void CGraphicView::OnLine() 
{
	// TODO: Add your command handler code here
	m_nDrawType=2;
}

void CGraphicView::OnRectangle() 
{
	// TODO: Add your command handler code here
	m_nDrawType=3;
}

void CGraphicView::OnEllipse() 
{
	// TODO: Add your command handler code here
	m_nDrawType=4;
}

void CGraphicView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_startDraw=true;//单击鼠标设置可以开始绘制
	m_ptOrigin=point;
	m_ptOld=point;
	/*摁下左键时保存点作为绘制其它图形时的起点*/
	::SetCursor(m_HCross);/*十字光标*/
	CScrollView::OnLButtonDown(nFlags, point);
}

void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_startDraw=false;/*重置绘图标志*/
	::ClipCursor(NULL);/*解锁光标，光标恢复成默认光标*/
	CClientDC dc(this);/*松开左键时开始绘制图形*/

	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);/*一个m_clr颜色的画笔*/
	dc.SelectObject(&pen);
	
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));/*透明画刷*/
	/*通过画刷的句柄返回指向CBrush的指针*/
	/*画刷句柄通过GetStockObject获取，记得类型转换*/

	dc.SelectObject(pBrush);/*将画刷选择到设备描述表中*/
	m_dcMetaFile.SelectObject(pBrush);/*元文件方法*/

	/*兼容DC法*/
	/*if(!m_dcCompatible.m_hAttribDC)如果没有创建兼容DC
	{
		m_dcCompatible.CreateCompatibleDC(&dc);/*与当前dc兼容
		CRect rect;
		GetClientRect(&rect);
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
		/*确认兼容DC的大小
		m_dcCompatible.SelectObject(&bitmap);
		m_dcCompatible.BitBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,SRCCOPY);
		m_dcCompatible.SelectObject(pBrush);
	}*/


	switch(m_nDrawType)/*根据用户选择绘制相应图形*/
	{
	case 1:
		dc.SetPixel(point,m_clr);
		/*该函数将指定坐标处的像素设为指定的颜色*/
		m_dcMetaFile.SetPixel(point,m_clr);
		//m_dcCompatible.SetPixel(point,RGB(0,0,0));
		break;
	case 2:
		//擦去MouseMove消息响应中绘制的最后一次临时线
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);

		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);

		m_dcMetaFile.MoveTo(m_ptOrigin);
		m_dcMetaFile.LineTo(point);

		//m_dcCompatible.MoveTo(m_ptOrigin);
		//m_dcCompatible.LineTo(point);
		break;
	case 3:
		dc.Rectangle(CRect(m_ptOrigin,m_ptOld));
		dc.Rectangle(CRect(m_ptOrigin,point));
		m_dcMetaFile.Rectangle(CRect(m_ptOrigin,point));
		//m_dcCompatible.Rectangle(CRect(m_ptOrigin,point));
		break;
	case 4:
		dc.Ellipse(CRect(m_ptOrigin,m_ptOld));
		dc.Ellipse(CRect(m_ptOrigin,point));
		m_dcMetaFile.Ellipse(CRect(m_ptOrigin,point));
		//m_dcCompatible.Ellipse(CRect(m_ptOrigin,point));
		break;
	}
	//CGraph graph(m_nDrawType,m_ptOrigin,point);
	//m_ptrArray.Add(&graph);/*保存对象的地址*/

	OnPrepareDC(&dc);
	dc.DPtoLP(&m_ptOrigin);/*设备点转逻辑点*/
	dc.DPtoLP(&point);/*由此滚动画布时不会出现底层上移现象*/

	CGraph *pGraph=new CGraph(m_nDrawType,m_ptOrigin,point,m_clr);
	m_ptrArray.Add(pGraph);/*保存堆中对象的地址*/

	CScrollView::OnLButtonUp(nFlags, point);

	
}

void CGraphicView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	OnPrepareDC(&dc);/*使画布滚动的时候不会被清屏*/
	OnDraw(&dc);
	// Do not call CScrollView::OnPaint() for painting messages
}

void CGraphicView::OnInitialUpdate() /*在打开窗口之后，第一次调用,也就是在onDraw()之前调用*/
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes(MM_TEXT,CSize(800,600));
}


void CGraphicView::OnFileSave() 
{
	// TODO: Add your command handler code here
	HMETAFILE hmetaFile;
	hmetaFile=m_dcMetaFile.Close();/*得到一个句柄*/
	CopyMetaFile(hmetaFile,"meta.wnf");/*保存*/
	m_dcMetaFile.Create();
	DeleteMetaFile(hmetaFile);
}

void CGraphicView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	HMETAFILE hmetaFile;
	hmetaFile=GetMetaFile("meta.wnf");
	m_dcMetaFile.PlayMetaFile(hmetaFile);
	DeleteMetaFile(hmetaFile);
	Invalidate();/*引起窗口的重画*/
}

void CGraphicView::OnSetting() 
{
	// TODO: Add your command handler code here
	CSettingDlg dlg;
	dlg.m_nLineWidth=m_nLineWidth;//使用户每次打开设置都能保存线宽值
	dlg.m_nLineStyle=m_nLineStyle;
	dlg.m_clr=m_clr;/*将view中保存的颜色传进去*/
	if(IDOK==dlg.DoModal())
	{
		m_nLineWidth=dlg.m_nLineWidth;
		m_nLineStyle=dlg.m_nLineStyle;//保存线型
	}
}

void CGraphicView::OnColor() 
{
	// TODO: Add your command handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags|=CC_RGBINIT | CC_FULLOPEN; //下条代码的前提（详见m_cc的说明） 
	//因为Flags在创建的时候就有一些参数了所以应该用或来添加CC_RGBINIT进去而不是赋值（覆盖），否则提示【非法】

	dlg.m_cc.rgbResult=m_clr;//保存回去
	if(IDOK==dlg.DoModal())//如果用户点击OK按钮
	{
		m_clr=dlg.m_cc.rgbResult;//rgbResult会保存用户的颜色选择
	}
}

void CGraphicView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CClientDC dc(this);/*获取设备句柄*/
	dc.SetROP2(R2_NOT);/*关键*/
	dc.SetROP2(R2_NOT);
	//所绘制的图形并没有消失
    //即：该函数用来定义绘制的颜色，而该参数则将颜色设置为原屏幕颜色的反色
	//这样，如果连续绘制两次的话，就可以恢复原来屏幕的颜色了（如下）
	//但是，这里的连续两次绘制却不是在一次消息响应中完成的
	//而是在第一次拖动响应的绘制可以显示（也就是看到的），第二次拖动绘制实现擦出（也就看不到了

	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);/*一个m_clr颜色的画笔*/
	dc.SelectObject(&pen);
	dc.SelectStockObject(NULL_BRUSH);
	//CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));/*透明画刷*/
	/*通过画刷的句柄返回指向CBrush的指针*/
	/*画刷句柄通过GetStockObject获取，记得类型转换*/
	//dc.SelectObject(pBrush);/*将画刷选择到设备描述表中*/
	if(m_startDraw==true)
	{
	switch(m_nDrawType)
	{
	case 0:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		m_ptOrigin=point;
		break;
	case 1:
		break;
	case 2:
		::SetCursor(m_HCross);
		/*擦去上一次所绘制的临时线*/
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);

		/*绘制这一次的临时线*/
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		
		//将临时线的终点复制给m_ptOld
		//使其在消息循环的过程中将该值传递到
		//擦去上一次画线的过程中，以便擦去上一次所画的线
		m_ptOld=point;
		break;
	case 3:
		::SetCursor(m_HCross);

		dc.Rectangle(CRect(m_ptOrigin,m_ptOld));
		dc.Rectangle(CRect(m_ptOrigin,point));
		
		m_ptOld=point;
		break;
	case 4:
		::SetCursor(m_HCross);

		dc.Ellipse(CRect(m_ptOrigin,m_ptOld));
		dc.Ellipse(CRect(m_ptOrigin,point));

		m_ptOld=point;
		break;
	}
	}
	CScrollView::OnMouseMove(nFlags, point);
}

BOOL CGraphicView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);

    BITMAP bmp;
	bitmap.GetBitmap(&bmp);
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);

	dcCompatible.SelectObject(&bitmap);

	CRect rect;
	GetClientRect(&rect);
//	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);
	pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,
		0,0,bmp.bmWidth(),bmp.bmHeight(),SRCCOPY);
	return true;
	//return CScrollView::OnEraseBkgnd(pDC);
}
