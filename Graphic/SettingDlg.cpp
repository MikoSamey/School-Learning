// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Graphic.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog


CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	m_nLineWidth = 0;
	m_nLineStyle = -1;
	//}}AFX_DATA_INIT
	m_clr=RGB(0,0,0);
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Text(pDX, IDC_LINE_WIDTH, m_nLineWidth);
	DDX_Radio(pDX, IDC_RADIO1, m_nLineStyle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_LINE_WIDTH, OnChangeLineWidth)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

void CSettingDlg::OnChangeLineWidth() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CSettingDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CSettingDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CSettingDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	Invalidate();
}

void CSettingDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	UpdateData();/*在过程中让控件值反映到成员变量*/
	/*完成线条绘制*/
	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);/*创建指定画笔*/
	dc.SelectObject(&pen);/*选中到设备描述表当中*/

	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);
	ScreenToClient(rect);
	/*先获取IDC_SAMPLE的指针，再用其去获取主窗口大小
	  如果直接调用GetWindowRect会得到对话框大小     */

	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);/*起点--左边靠中间*/
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);/*终点--右边靠中--画线*/
	// Do not call CDialog::OnPaint() for painting messages
}