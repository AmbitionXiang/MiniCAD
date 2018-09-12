// Dlg5.cpp : implementation file
//

#include "stdafx.h"
#include "line.h"
#include "Dlg5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg5 dialog


CDlg5::CDlg5(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg5::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg5)
	m_Edit2 = 1;
	//}}AFX_DATA_INIT
}


void CDlg5::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg5)
	DDX_Text(pDX, IDC_EDIT2, m_Edit2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg5, CDialog)
	//{{AFX_MSG_MAP(CDlg5)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg5 message handlers

void CDlg5::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDlg5::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlg5::OnChangeEdit2() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}
