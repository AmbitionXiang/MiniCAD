#if !defined(AFX_DLG2_H__DCD865D8_907B_48D1_A6C5_ECB2CC2DAB11__INCLUDED_)
#define AFX_DLG2_H__DCD865D8_907B_48D1_A6C5_ECB2CC2DAB11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg2 dialog

class CDlg2 : public CDialog
{
// Construction
public:
	CDlg2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg2)
	enum { IDD = IDD_DIALOG2 };
	CComboBox	m_Type;
	int		m_Color1;
	int		m_Color2;
	int		m_Color3;
	long	m_Width;
	int		m_TypeIndex;
	BOOL	m_AutoShowPar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg2)
	afx_msg void OnSelchangeType();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG2_H__DCD865D8_907B_48D1_A6C5_ECB2CC2DAB11__INCLUDED_)
