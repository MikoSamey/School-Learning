// CAD_BezierView.cpp : implementation of the CCAD_BezierView class
//

#include "stdafx.h"
#include "CAD_Bezier.h"

#include "CAD_BezierDoc.h"
#include "CAD_BezierView.h"

#include <math.h>
#define N_MAX_POINT 10	//���Ŀ��Ƶ���Ŀ
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
	m_bFlag = 1;			//���Ի��ƿ��Ƶ�
	pt=new CPoint[N_MAX_POINT];
	p = new double[N_MAX_POINT];
	CtrlPNum = 0;
	m_iDrawType = -1;		//δѡ����Ʒ�ʽ
	m_bDrawStruct = FALSE;	//���ܻ���b�����ṹͼ
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
	* ˫������ƿ��Ƶ��Լ���Ӧ������
	*/
	CRect rect;
	GetClientRect(&rect);//��ÿͻ����Ĵ�С
////////////////
	CDC memDC;//�ڴ�DC
	CBitmap NewBitmap,*pOldBitmap;	//�ڴ��г���ͼ�����ʱλͼ
	memDC.CreateCompatibleDC(pDC);	//��������ĻpDC���ݵ�memDC
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//��������λͼ---�ͻ�����С��pDC�豸

	pOldBitmap = memDC.SelectObject(&NewBitmap);	//������λͼѡ��memDC
	memDC.FillSolidRect(rect,pDC->GetBkColor());	//��ԭ���������ͻ����������Ǻ�ɫ

    memDC.BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);

	DrawCtrPloygon(&memDC);
	switch(m_iDrawType)
	{
	case -1:
		//��ʾ��Ϣ�ĶԻ���
		MessageBox("��ʹ��������ѡȡ���Ƶ㣬�Ҽ����Ƶ��ƶ�\n\n\t����˵�ѡ�������Ӧ����","��ʾ",MB_OK);
		m_iDrawType = -2;
		break;
	case 0:
		memDC.TextOut(50,50,"����Bezier���ߣ�");
		DrawBezier(&memDC);
		break;
	case 1:
		memDC.TextOut(50,50,"����B�������ߣ�");
		B3Curves(pt,&memDC);
		if(m_bDrawStruct)
		{
			DrawBSplineStruct(&memDC);
		}
		break;
	case 3:
		memDC.TextOut(50,50,"����Hermite���ߣ�");
		if(CtrlPNum >= 4)
		{
			DrawHermite(&memDC);
		}
		break;
	default:
		break;
	}

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);

	memDC.SelectObject(pOldBitmap);	//�ָ�λͼ
	NewBitmap.DeleteObject();	//ɾ��λͼ
	memDC.DeleteDC();			//ɾ��memDC

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

/*����Hermite����*/
void CCAD_BezierView::DrawHermite(CDC *pDC)
{
	if(CtrlPNum < 4) //�������4�����Ƶ�
		return;	//���أ��޷�����

	CPoint p0,p1,p0_tg,p1_tg; //����յ㣬�Լ�������������2����

	p0 = pt[0];p1 = pt[2];
	
	p0_tg.x = pt[1].x - pt[0].x;
	p0_tg.y = pt[1].y - pt[0].y;

	p1_tg.x = pt[3].x - pt[2].x;
	p1_tg.y = pt[3].y - pt[2].y;

	double delt = 1.0/1000;	//����,�����Ƶ�ľ��뻮�ֳ�1000�ȷ�
	CPoint p;//�����ϵĵ�
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

/*���ƶ�ά����ʱ���¿�˹����º�������������*/
long CCAD_BezierView::DeCasteliau(double t, long *p)
{
	double P[N_MAX_POINT][N_MAX_POINT];
	int n = CtrlPNum-1;	
	for(int k = 0;k<=n;k++)
	{
		P[0][k] = p[k];	//p[]���ŵ��ǵ�����������x�ᡢy�ᣩ
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

/*����Bezier����*/
void CCAD_BezierView::DrawBezier(CDC *pDC)
{
	double delt = 1.0/5000;	//����,�����Ƶ�ľ��뻮�ֳ�5000�ȷ�
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
		p.x = DeCasteliau(t, px);//x����
		p.y = DeCasteliau(t, py);//y����
		pDC->SetPixel(p.x,p.y,RGB(255,0,255));
	}

}

/*����B��������*/
void CCAD_BezierView::B3Curves(CPoint p[], CDC *pDC)
{
	double delt = 1.0/10;
	CPoint PStart,PEnd;			//ÿ��B�������ߵ������յ�
	double F03,F13,F23,F33;		//B����������

	PStart.x = long((pt[0].x+4.0*pt[1].x+pt[2].x)/6.0);	//t = 0�����x����
	PStart.y = long((pt[0].y+4.0*pt[1].y+pt[2].y)/6.0); //t = 0�����y����
	pDC->MoveTo(PStart);

	CPen NewPen1(PS_SOLID,2,RGB(255,0,0));
	CPen *OldPen1=pDC->SelectObject(&NewPen1);

	for(int i=1;i <= CtrlPNum-3;i++)	//4�����Ƶ����һ��B��������
	{
		for(double t=0;t<=1;t+=delt)
		{
			F03 = (-t*t*t+3*t*t-3*t+1)/6;//����F0,3(t)
			F13 = (3*t*t*t-6*t*t+4)/6;//����F1,3(t)
			F23 = (-3*t*t*t+3*t*t+3*t+1)/6;//����F2,3(t)
			F33 = t*t*t/6;//����B3,3(t)

			PEnd.x = long(pt[i-1].x*F03+pt[i].x*F13+pt[i+1].x*F23+pt[i+2].x*F33);
			PEnd.y = long(pt[i-1].y*F03+pt[i].y*F13+pt[i+1].y*F23+pt[i+2].y*F33);
			pDC->LineTo(PEnd);
		}
	}
	pDC->SelectObject(OldPen1);
	NewPen1.DeleteObject();	

}

/*����B�������νṹ*/
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

/*���ƿ��Ƶ�����*/
void CCAD_BezierView::DrawCtrPloygon(CDC *pDC)
{	
	CPen NewPen, *pOldPen;					//���2�ĺڱ�
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));
	pOldPen = pDC->SelectObject(&NewPen);

	CBrush NewBrush, *pOldBrush;			//ʵ�ĺ�ˢ��
	NewBrush.CreateSolidBrush(RGB(0,0,0));
	pOldBrush = pDC->SelectObject(&NewBrush);

	if(m_iDrawType != 3) //��Hermite����
	{
	for(int i = 0;i<CtrlPNum;i++)
	{
		if(0 == i) //��Ե�һ����
		{
			pDC->MoveTo(pt[i].x,pt[i].y);
			pDC->Ellipse(pt[i].x-4,pt[i].y-4,pt[i].x+4,pt[i].y+4); //�뾶Ϊ1��ʵ��Բ����ʾ���Ƶ�
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
	//�������
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();

	pDC->SelectObject(pOldPen);
	NewPen.DeleteObject();

}


////////////////////////////�����Ӧ����////////////////////////////

/*
* ����������
* ���λ�õ� = ���Ƶ� �� ͬʱ���� DrawCtrPolygon() �������ƿ��ƶ����
*/
void CCAD_BezierView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bFlag)	//���Ի�ͼ
	{
		pt[CtrlPNum] = point;
		if(CtrlPNum < N_MAX_POINT)
		{
			CtrlPNum++;
		}
		else
		{
			m_bFlag = FALSE;	//�������ֵ�Ͳ��ٻ�����
		}
	}

	Invalidate(FALSE);

	CView::OnLButtonDown(nFlags, point);
}

/*�������Ҽ���������*/
void CCAD_BezierView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bFlag = FALSE;

	if (TRUE == m_AbleToLeftBtn)//���λ�ڿ��Ƶ㸽��
	{
		m_AbleToMove = TRUE;//��갴�£���ʼ�ƶ�
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
	m_AbleToMove = FALSE;//ֹͣ�ƶ����ػ�
	Invalidate(FALSE);
	CView::OnRButtonUp(nFlags, point);
}

/*�ƶ����ʱ״̬����ʾ���λ������ֵ*/
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
	m_i = -1;	//Ĭ��-1
	
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


////////////////�˵���Ӧ����---ѡ���������//////////////

void CCAD_BezierView::OnMenuHermite() //Hermite����
{
	// TODO: Add your command handler code here
	m_iDrawType = 3;
	Invalidate(FALSE);
}

void CCAD_BezierView::OnBezierAlg() //Bezier����
{
	// TODO: Add your command handler code here
	//ClearMemory();
	m_iDrawType = 0;
	Invalidate(FALSE);
}

void CCAD_BezierView::OnBsplineAlg() //B��������
{
	// TODO: Add your command handler code here
	//ClearMemory();
	m_iDrawType = 1;
	Invalidate(FALSE);
}

/*B�������ߵļ��νṹ*/
void CCAD_BezierView::OnMenuStruct() 
{
	// TODO: Add your command handler code here
	m_bDrawStruct = TRUE;
	Invalidate(FALSE);
}

//////////////////////////////////////////////
/*�����Ա����*/
void CCAD_BezierView::ClearMemory()
{
	//RedrawWindow();
	if(pt != 0)
	{
		delete pt;
		pt=new CPoint[N_MAX_POINT];
	}
	CtrlPNum = 0;
	m_bFlag = TRUE;			//���Զ�����Ƶ�
	m_iDrawType = -2;		//δѡ����Ʒ�ʽ
	m_bDrawStruct = FALSE;	//���ܻ���b�����ṹͼ
	m_i = -1;				//�����޸Ŀ��Ƶ�
}

void CCAD_BezierView::OnMenuClear() 
{
	// TODO: Add your command handler code here
	ClearMemory();
	Invalidate(FALSE);
}

