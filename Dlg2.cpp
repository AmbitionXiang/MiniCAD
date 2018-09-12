// Dlg2.cpp : implementation file
//

#include "stdafx.h"
#include "Line.h"
#include "Dlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg2 dialog


CDlg2::CDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg2)
	m_Color1 = 10;
	m_Color2 = 10;
	m_Color3 = 255;
	m_Width = 1;
	m_TypeIndex = -1;
	m_AutoShowPar = FALSE;
	//}}AFX_DATA_INIT
}


void CDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg2)
	DDX_Control(pDX, IDC_TYPE, m_Type);
	DDX_Text(pDX, IDC_COLOR1, m_Color1);
	DDV_MinMaxInt(pDX, m_Color1, 0, 255);
	DDX_Text(pDX, IDC_COLOR2, m_Color2);
	DDV_MinMaxInt(pDX, m_Color2, 0, 255);
	DDX_Text(pDX, IDC_COLOR3, m_Color3);
	DDV_MinMaxInt(pDX, m_Color3, 0, 255);
	DDX_Text(pDX, IDC_WIDTH, m_Width);
	DDX_CBIndex(pDX, IDC_TYPE, m_TypeIndex);
	DDX_Check(pDX, IDC_CHECK1, m_AutoShowPar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg2, CDialog)
	//{{AFX_MSG_MAP(CDlg2)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg2 message handlers

void CDlg2::OnSelchangeType() 
{
	// TODO: Add your control notification handler code here
	m_TypeIndex=m_Type.GetCurSel();                                   //////
}

void CDlg2::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}

void CDlg2::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CDlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Type.InsertString(0,"实线");                           //////
	m_Type.InsertString(1,"点线");
	m_Type.InsertString(2,"划线");
	m_Type.InsertString(3,"点划线");
	m_Type.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDlg2::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	
}
