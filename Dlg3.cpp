// Dlg3.cpp : implementation file
//

#include "stdafx.h"
#include "line.h"
#include "Dlg3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg3 dialog


CDlg3::CDlg3(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg3::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg3)
	m_DlgAngle =90.0;
	m_ArcType = 1;
	//}}AFX_DATA_INIT
}


void CDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg3)
	DDX_Text(pDX, IDC_EDIT1, m_DlgAngle);
	DDX_Radio(pDX, IDC_THREEPOINTARC, m_ArcType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg3, CDialog)
	//{{AFX_MSG_MAP(CDlg3)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_BN_CLICKED(IDC_THREEPOINTARC, OnChooseArc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg3 message handlers

void CDlg3::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDlg3::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg3::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_ArcType==1)
	UpdateData(TRUE);
}

void CDlg3::OnChooseArc() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

}
