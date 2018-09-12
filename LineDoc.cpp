// LineDoc.cpp : implementation of the CLineDoc class
//

#include "stdafx.h"
#include "Line.h"

#include "LineDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineDoc

IMPLEMENT_DYNCREATE(CLineDoc, CDocument)

BEGIN_MESSAGE_MAP(CLineDoc, CDocument)
	//{{AFX_MSG_MAP(CLineDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineDoc construction/destruction

CLineDoc::CLineDoc()
{
	// TODO: add one-time construction code here
	InterPNum=0;                               //////
	InterPList=new CPoint[1000];               //////
}

CLineDoc::~CLineDoc()
{
	delete[]InterPList;
}

BOOL CLineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here

	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CLineDoc serialization

void CLineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CLineDoc diagnostics

#ifdef _DEBUG
void CLineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLineDoc commands

CPline * CLineDoc::AddPline(int Number, CPoint *PointList,int type,int width,COLORREF color)//增加连续折线对象
{
	CPline *p_Pline=new CPline(Number,PointList);
	LOGPEN lopn;
	switch(type)
	{
	case 0:lopn.lopnStyle=PS_SOLID;lopn.lopnWidth.x=width;break;
	case 1:lopn.lopnStyle=PS_DOT;lopn.lopnWidth.x=1;break;
	case 2:lopn.lopnStyle=PS_DASH;lopn.lopnWidth.x=1;break;
	case 3:lopn.lopnStyle=PS_DASHDOT;lopn.lopnWidth.x=1;break;
	}
	lopn.lopnColor=color;
	p_Pline->pen[m_PLineArray.GetUpperBound()+1].CreatePenIndirect(&lopn);     
	m_PLineArray.Add(p_Pline);
	//CString str;
	//str.Format("%d",m_PLineArray.GetUpperBound()+1);
	//AfxMessageBox(str);
	return p_Pline;

}

void CLineDoc::Draw(CDC *pDC)
{
	int nn=m_PLineArray.GetUpperBound()+1;//得到存储第i类图形元素对象指针数组的最大下标
	while(nn--)
	{
		m_PLineArray.GetAt(nn)->Draw(pDC,nn);
	}
}

CPline * CLineDoc::AddParPline(int Number, CPoint *PointList) //添加平行线对象
{
	CPline *p_Pline=new CPline(Number,PointList);
	m_ParPLineArray.Add(p_Pline);
	//CString str;
	//str.Format("%d",m_PLineArray.GetUpperBound()+1);
	//AfxMessageBox(str);
	return p_Pline;
}

void CLineDoc::DrawPar(CDC *pDC,CPoint &ParFlag)
{
	int nn=m_ParPLineArray.GetUpperBound()+1;//得到存储第i类图形元素对象指针数组的最大下标
	while(nn--)
	{
		m_ParPLineArray.GetAt(nn)->DrawPar(pDC,ParFlag);
	}
}
