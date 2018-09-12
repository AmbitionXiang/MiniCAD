#if !defined(AFX_DLG4_H__E4913756_9365_448D_A519_EED2D3779422__INCLUDED_)
#define AFX_DLG4_H__E4913756_9365_448D_A519_EED2D3779422__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg4.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg4 dialog

class CDlg4 : public CDialog
{
// Construction
public:
	CDlg4(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg4)
	enum { IDD = IDD_DIALOG4 };
	double	m_Angle;
	int		m_radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg4)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg4)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG4_H__E4913756_9365_448D_A519_EED2D3779422__INCLUDED_)
