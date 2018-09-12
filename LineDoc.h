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
	CTypedPtrArray<CObArray,CPline*>m_PLineArray;//管理连续线对象的指针数组
	CTypedPtrArray<CObArray,CPline*>m_ParPLineArray;          //////
	/*新数据成员m_LineArray是MFC类样板CTypedPrtArray的实例。CTypedPtrArray生成一族类，各由第一个样板参数指定的派生，
	各用于存放第二个参数指定类型的数据项。这样m_LineArray是CObArray派生的类的对象，存放CLine对象的指针。
	使用派生类的原因是他的编译器能进行更广泛的类型检查，帮助减少错误，并减少使用类对象时需要的校正操作。
	为了使用CTypedPtrArray或者其他的任何MFC类样板，必须包含AfxTempl.h头文件，将其加入到StdAfx.h文件中。
	删除数据的时候，必须先用DELETE命令删除对象，然后使用类的删除命令，删除对象的指针。*/
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
	CPline * AddPline(int Number, CPoint *PointList,int type,int width,COLORREF color);//增加连续折线对象
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEDOC_H__784A2559_25DC_4B1A_83C9_D5B0796B6CD6__INCLUDED_)
