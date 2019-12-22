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
	m_nDrawType=0;/*���������û���ѡ��*/
	m_ptOrigin=0;/*���*/
	m_ptOld=0;/*�ɵ�*/
	m_nLineWidth=0;/*�߿�*/
	m_nLineStyle=0;/*����*/

	m_startDraw=false;/*��̬���ߵĻ�����û�л���������*/

	/*��ʼ��m_HCrossΪʮ�ֹ��*/
	m_HCross=AfxGetApp()->LoadStandardCursor(IDC_CROSS);

	m_clr=RGB(255,0,0);

	m_dcMetaFile.Create();
	/*����ΪNULL--�µ��ڴ�Ԫ�ļ�*/
	/*����Ϊ�ļ���---�µ�Ԫ�ļ�*/
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
	/*�������ͼ��ȡ����*/
	
	
	//CPen pen(m_nLineStyle,m_nLineWidth,m_clr);/*һ��m_clr��ɫ�Ļ���*/
	//pDC->SelectObject(&pen);

	//CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//͸����ˢ
	//pDC->SelectObject(pBrush);

	for(int i=0;i<m_ptrArray.GetSize();i++)
	{
		m_clr=((CGraph*)m_ptrArray.GetAt(i))->m_clr;
		CPen pen(m_nLineStyle,m_nLineWidth,m_clr);/*һ��m_clr��ɫ�Ļ���*/
		pDC->SelectObject(&pen);

		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//͸����ˢ
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
	m_startDraw=true;//����������ÿ��Կ�ʼ����
	m_ptOrigin=point;
	m_ptOld=point;
	/*�������ʱ�������Ϊ��������ͼ��ʱ�����*/
	::SetCursor(m_HCross);/*ʮ�ֹ��*/
	CScrollView::OnLButtonDown(nFlags, point);
}

void CGraphicView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_startDraw=false;/*���û�ͼ��־*/
	::ClipCursor(NULL);/*������꣬���ָ���Ĭ�Ϲ��*/
	CClientDC dc(this);/*�ɿ����ʱ��ʼ����ͼ��*/

	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);/*һ��m_clr��ɫ�Ļ���*/
	dc.SelectObject(&pen);
	
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));/*͸����ˢ*/
	/*ͨ����ˢ�ľ������ָ��CBrush��ָ��*/
	/*��ˢ���ͨ��GetStockObject��ȡ���ǵ�����ת��*/

	dc.SelectObject(pBrush);/*����ˢѡ���豸��������*/
	m_dcMetaFile.SelectObject(pBrush);/*Ԫ�ļ�����*/

	/*����DC��*/
	/*if(!m_dcCompatible.m_hAttribDC)���û�д�������DC
	{
		m_dcCompatible.CreateCompatibleDC(&dc);/*�뵱ǰdc����
		CRect rect;
		GetClientRect(&rect);
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
		/*ȷ�ϼ���DC�Ĵ�С
		m_dcCompatible.SelectObject(&bitmap);
		m_dcCompatible.BitBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,SRCCOPY);
		m_dcCompatible.SelectObject(pBrush);
	}*/


	switch(m_nDrawType)/*�����û�ѡ�������Ӧͼ��*/
	{
	case 1:
		dc.SetPixel(point,m_clr);
		/*�ú�����ָ�����괦��������Ϊָ������ɫ*/
		m_dcMetaFile.SetPixel(point,m_clr);
		//m_dcCompatible.SetPixel(point,RGB(0,0,0));
		break;
	case 2:
		//��ȥMouseMove��Ϣ��Ӧ�л��Ƶ����һ����ʱ��
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
	//m_ptrArray.Add(&graph);/*�������ĵ�ַ*/

	OnPrepareDC(&dc);
	dc.DPtoLP(&m_ptOrigin);/*�豸��ת�߼���*/
	dc.DPtoLP(&point);/*�ɴ˹�������ʱ������ֵײ���������*/

	CGraph *pGraph=new CGraph(m_nDrawType,m_ptOrigin,point,m_clr);
	m_ptrArray.Add(pGraph);/*������ж���ĵ�ַ*/

	CScrollView::OnLButtonUp(nFlags, point);

	
}

void CGraphicView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	OnPrepareDC(&dc);/*ʹ����������ʱ�򲻻ᱻ����*/
	OnDraw(&dc);
	// Do not call CScrollView::OnPaint() for painting messages
}

void CGraphicView::OnInitialUpdate() /*�ڴ򿪴���֮�󣬵�һ�ε���,Ҳ������onDraw()֮ǰ����*/
{
	CScrollView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes(MM_TEXT,CSize(800,600));
}


void CGraphicView::OnFileSave() 
{
	// TODO: Add your command handler code here
	HMETAFILE hmetaFile;
	hmetaFile=m_dcMetaFile.Close();/*�õ�һ�����*/
	CopyMetaFile(hmetaFile,"meta.wnf");/*����*/
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
	Invalidate();/*���𴰿ڵ��ػ�*/
}

void CGraphicView::OnSetting() 
{
	// TODO: Add your command handler code here
	CSettingDlg dlg;
	dlg.m_nLineWidth=m_nLineWidth;//ʹ�û�ÿ�δ����ö��ܱ����߿�ֵ
	dlg.m_nLineStyle=m_nLineStyle;
	dlg.m_clr=m_clr;/*��view�б������ɫ����ȥ*/
	if(IDOK==dlg.DoModal())
	{
		m_nLineWidth=dlg.m_nLineWidth;
		m_nLineStyle=dlg.m_nLineStyle;//��������
	}
}

void CGraphicView::OnColor() 
{
	// TODO: Add your command handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags|=CC_RGBINIT | CC_FULLOPEN; //���������ǰ�ᣨ���m_cc��˵���� 
	//��ΪFlags�ڴ�����ʱ�����һЩ����������Ӧ���û������CC_RGBINIT��ȥ�����Ǹ�ֵ�����ǣ���������ʾ���Ƿ���

	dlg.m_cc.rgbResult=m_clr;//�����ȥ
	if(IDOK==dlg.DoModal())//����û����OK��ť
	{
		m_clr=dlg.m_cc.rgbResult;//rgbResult�ᱣ���û�����ɫѡ��
	}
}

void CGraphicView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CClientDC dc(this);/*��ȡ�豸���*/
	dc.SetROP2(R2_NOT);/*�ؼ�*/
	dc.SetROP2(R2_NOT);
	//�����Ƶ�ͼ�β�û����ʧ
    //�����ú�������������Ƶ���ɫ�����ò�������ɫ����Ϊԭ��Ļ��ɫ�ķ�ɫ
	//��������������������εĻ����Ϳ��Իָ�ԭ����Ļ����ɫ�ˣ����£�
	//���ǣ�������������λ���ȴ������һ����Ϣ��Ӧ����ɵ�
	//�����ڵ�һ���϶���Ӧ�Ļ��ƿ�����ʾ��Ҳ���ǿ����ģ����ڶ����϶�����ʵ�ֲ�����Ҳ�Ϳ�������

	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);/*һ��m_clr��ɫ�Ļ���*/
	dc.SelectObject(&pen);
	dc.SelectStockObject(NULL_BRUSH);
	//CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));/*͸����ˢ*/
	/*ͨ����ˢ�ľ������ָ��CBrush��ָ��*/
	/*��ˢ���ͨ��GetStockObject��ȡ���ǵ�����ת��*/
	//dc.SelectObject(pBrush);/*����ˢѡ���豸��������*/
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
		/*��ȥ��һ�������Ƶ���ʱ��*/
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld);

		/*������һ�ε���ʱ��*/
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		
		//����ʱ�ߵ��յ㸴�Ƹ�m_ptOld
		//ʹ������Ϣѭ���Ĺ����н���ֵ���ݵ�
		//��ȥ��һ�λ��ߵĹ����У��Ա��ȥ��һ����������
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
