// Dlg4.cpp : implementation file
//

#include "stdafx.h"
#include "line.h"
#include "Dlg4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg4 dialog


CDlg4::CDlg4(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg4)
	m_Angle =90;
	m_radio =0;
	//}}AFX_DATA_INIT
}


void CDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg4)
	DDX_Text(pDX, IDC_ANGLE, m_Angle);
	DDX_Radio(pDX, IDC_LINE, m_radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg4, CDialog)
	//{{AFX_MSG_MAP(CDlg4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg4 message handlers

void CDlg4::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	
	CDialog::OnOK();
}

void CDlg4::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
