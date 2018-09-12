#if !defined(AFX_DLG6_H__F551C7AB_52C5_4DD1_8A33_A8AF76299C1C__INCLUDED_)
#define AFX_DLG6_H__F551C7AB_52C5_4DD1_8A33_A8AF76299C1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg6.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg6 dialog

class CDlg6 : public CDialog
{
// Construction
public:
	CDlg6(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg6)
	enum { IDD = IDD_DIALOG6 };
	int		m_Edit1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg6)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg6)
	afx_msg void OnChangeEdit1();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG6_H__F551C7AB_52C5_4DD1_8A33_A8AF76299C1C__INCLUDED_)
