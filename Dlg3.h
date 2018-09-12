#if !defined(AFX_DLG3_H__6F7244FE_6DAE_4255_BAC3_4F94C7430314__INCLUDED_)
#define AFX_DLG3_H__6F7244FE_6DAE_4255_BAC3_4F94C7430314__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg3.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg3 dialog

class CDlg3 : public CDialog
{
// Construction
public:
	CDlg3(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg3)
	enum { IDD = IDD_DIALOG3 };
	double	m_DlgAngle;
	int		m_ArcType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg3)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg3)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChooseArc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG3_H__6F7244FE_6DAE_4255_BAC3_4F94C7430314__INCLUDED_)
