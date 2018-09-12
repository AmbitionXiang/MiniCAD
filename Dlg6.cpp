// Dlg6.cpp : implementation file
//

#include "stdafx.h"
#include "line.h"
#include "Dlg6.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg6 dialog


CDlg6::CDlg6(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg6::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg6)
	m_Edit1 = 1;
	//}}AFX_DATA_INIT
}


void CDlg6::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg6)
	DDX_Text(pDX, IDC_EDIT1, m_Edit1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg6, CDialog)
	//{{AFX_MSG_MAP(CDlg6)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg6 message handlers

void CDlg6::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CDlg6::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDlg6::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
