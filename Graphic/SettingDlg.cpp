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
	UpdateData();/*�ڹ������ÿؼ�ֵ��ӳ����Ա����*/
	/*�����������*/
	CPen pen(m_nLineStyle,m_nLineWidth,m_clr);/*����ָ������*/
	dc.SelectObject(&pen);/*ѡ�е��豸��������*/

	CRect rect;
	GetDlgItem(IDC_SAMPLE)->GetWindowRect(&rect);
	ScreenToClient(rect);
	/*�Ȼ�ȡIDC_SAMPLE��ָ�룬������ȥ��ȡ�����ڴ�С
	  ���ֱ�ӵ���GetWindowRect��õ��Ի����С     */

	dc.MoveTo(rect.left+20,rect.top+rect.Height()/2);/*���--��߿��м�*/
	dc.LineTo(rect.right-20,rect.top+rect.Height()/2);/*�յ�--�ұ߿���--����*/
	// Do not call CDialog::OnPaint() for painting messages
}