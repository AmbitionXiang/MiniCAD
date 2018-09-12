#if !defined(AFX_DLG5_H__F7AB6FD4_1048_4FF9_922D_2A0408EF53D5__INCLUDED_)
#define AFX_DLG5_H__F7AB6FD4_1048_4FF9_922D_2A0408EF53D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg5.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg5 dialog

class CDlg5 : public CDialog
{
// Construction
public:
	CDlg5(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg5)
	enum { IDD = IDD_DIALOG5 };
	int		m_Edit2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg5)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg5)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeEdit2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG5_H__F7AB6FD4_1048_4FF9_922D_2A0408EF53D5__INCLUDED_)
