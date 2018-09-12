// LineDoc.h : interface of the CLineDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINEDOC_H__784A2559_25DC_4B1A_83C9_D5B0796B6CD6__INCLUDED_)
#define AFX_LINEDOC_H__784A2559_25DC_4B1A_83C9_D5B0796B6CD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"Pline.h"
#include"Arc.h"
class CLineDoc : public CDocument
{
protected: // create from serialization only
	CLineDoc();
	DECLARE_DYNCREATE(CLineDoc)

// Attributes
public:
	CTypedPtrArray<CObArray,CPline*>m_PLineArray;//���������߶����ָ������
	CTypedPtrArray<CObArray,CPline*>m_ParPLineArray;          //////
	/*�����ݳ�Աm_LineArray��MFC������CTypedPrtArray��ʵ����CTypedPtrArray����һ���࣬���ɵ�һ���������ָ����������
	�����ڴ�ŵڶ�������ָ�����͵����������m_LineArray��CObArray��������Ķ��󣬴��CLine�����ָ�롣
	ʹ���������ԭ�������ı������ܽ��и��㷺�����ͼ�飬�������ٴ��󣬲�����ʹ�������ʱ��Ҫ��У��������
	Ϊ��ʹ��CTypedPtrArray�����������κ�MFC�����壬�������AfxTempl.hͷ�ļ���������뵽StdAfx.h�ļ��С�
	ɾ�����ݵ�ʱ�򣬱�������DELETE����ɾ������Ȼ��ʹ�����ɾ�����ɾ�������ָ�롣*/
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLineDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void DrawPar(CDC *pDC,CPoint &ParFlag);
	CPline * AddParPline(int Number, CPoint *PointList);
	int InterPNum;
	CPoint *InterPList;
	void Draw(CDC *pDC);
	CPline * AddPline(int Number, CPoint *PointList,int type,int width,COLORREF color);//�����������߶���
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEDOC_H__784A2559_25DC_4B1A_83C9_D5B0796B6CD6__INCLUDED_)
