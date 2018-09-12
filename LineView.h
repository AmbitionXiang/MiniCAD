// LineView.h : interface of the CLineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINEVIEW_H__63E4C379_A7BF_4276_8317_DEE479E9DE30__INCLUDED_)
#define AFX_LINEVIEW_H__63E4C379_A7BF_4276_8317_DEE479E9DE30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"Dlg.h"
#include "Dlg2.h"	// Added by ClassView
#include "Dlg3.h"	// Added by ClassView
#include "Dlg4.h"
#include "Arc.h"	// Added by ClassView
#include "Dlg5.h"	// Added by ClassView
#include "Dlg6.h"
class CLineView : public CView
{
protected: // create from serialization only
	CLineView();
	DECLARE_DYNCREATE(CLineView)

// Attributes
public:
	CLineDoc* GetDocument();  //��ȡ�ĵ�ָ��

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:

	bool MultiNearFlag;
	double Distance;
	bool MultiStartFlag;
	int MultiNum;      //�����϶����ߵ�����
	int Multi[100][2];    //��������Ϣ
	CPoint MultiStart[1000];
	CPen pen,*pOldPen;
	BOOL m_MultiOpen;
	CDlg6 dlg6;
	CDlg5 dlg5;
	CDlg4 dlg4;
	CDlg3 dlg3;
	CDlg2 dlg2; 
	CArc Arc;
	BOOL ShowIPFlag;                     //�Ƿ���ʾ����
	CPoint ParFlag;						//��ƽ���߻���ɾ��ƽ����
	BOOL AutoShowPar;                   //�Ƿ��Զ���ʾƽ����
	double a,b,c,A,B,C;                                                   //////
	void ChangePen(CPen &pen,int type,int width,COLORREF color);          //////
	virtual ~CLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLineView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnPar();
	afx_msg void OnCleanpar();
	afx_msg void OnFileNew();
	afx_msg void OnDrawCross();
	afx_msg void OnCleanCross();
	afx_msg void OnArc();
	afx_msg void OnMultiline();
	afx_msg void OnMultistart();
	afx_msg void OnNear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDlg dlg;//����Ի���
	int ArcFlag;//������ʶ��
	bool TPFlag;//���㻭��ת���ʶ��
	//�����ߵ�ƽ���ߣ������ĺ�������Ϊ�豸��ָ�룬���ڻ�ͼ��
	//��������ָ�룬���������е�ĸ�����ƽ�м��
	void DrawPar(CDC *pDC,CPoint *PointList,int Number,int t);

	int multi(CPoint p1,CPoint p2,CPoint p0);
	bool IsIntersect(CPoint s1,CPoint e1,CPoint s2,CPoint e2);
	int m_nPushNum;//��갴�µĴ���
	CPoint *m_PointList;//����Ѿ����µ����������
	CPoint m_ptOrigin;//��¼��갴�µĵ�
	CPoint m_ptOldPoint;//��¼��갴�µĵ�
	int m_nLineStyle;//����
	int m_nLineWidth;//�߿�
	COLORREF m_nLineColor;//��ɫ
	int m_bType;//ѡ����ģʽ
};

#ifndef _DEBUG  // debug version in LineView.cpp
inline CLineDoc* CLineView::GetDocument()
   { return (CLineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEVIEW_H__63E4C379_A7BF_4276_8317_DEE479E9DE30__INCLUDED_)





















