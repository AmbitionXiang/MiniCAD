// Pline.cpp: implementation of the CPline class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Line.h"
#include "Pline.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction


CPline::CPline()
{
	m_LineType=1;
	m_ColorPen=RGB(0,0,255);
	m_Number=0;
	m_PointList=NULL;//初始设置顶点数组为NULL
	
}

CPline::~CPline()
{

}

void CPline::Draw(CDC *pDC,int n)
{ 
	CPen *pOldPen=pDC->SelectObject(&pen[n]);
	/*i. 要使画笔生效就必须先将创建好的CPen对象选入dc设备环境中；
ii. 使用SelectObject将绘图对象选入环境设备dc中：CPen* SelectObject(CPen* pPen);，其返回更新之前的老画笔的句柄；
iii. MFC将SelectObject重载过好几个版本的，有CBrush等其它类型的绘图对象，这里只是画笔一种而已；
iv. CPen* pOldPen = dc.SelectObject(pNewPen);*/

	CPoint *ppoint;  //创建一个点的数组指针

	ppoint=new CPoint[m_Number+1];//动态创建一个点的数组
	for(int i=0;i<m_Number;i++)//将顶点坐标转化成实际坐标,存放到ppoint中
	{	
		
		ppoint[i].x=m_PointList[i].x;   
		ppoint[i].y=m_PointList[i].y;
	}
	
		pDC->MoveTo(ppoint[0].x,ppoint[0].y);   //移动当前位置 
	for(i=1;i<m_Number;i++) 
	{
		pDC->LineTo(ppoint[i].x,ppoint[i].y);    //从当前位置到一点画直线，但不包括那个点 
	}
	delete  []ppoint;//删除原来动态分配的数组
	pDC->SelectObject(pOldPen);//恢复原来的画笔
	//pen[n].DeleteObject();
	
}

CPline::CPline(int Number,CPoint *PointList)
{
	m_Number=Number;

	m_PointList=new CPoint[Number+1];//动态分配空间
	
	if(Number>0)
	{
		for(int i=0;i<Number;i++)
		{
			m_PointList[i]=PointList[i];
		}
	}
	
}

int CPline::GetNumber()
{
	return m_Number;
}


CPoint* CPline::GetPList()
{
	return m_PointList;
}

void CPline::GetParam(double &A,double &B,double &C,CPoint m_ptStart,CPoint m_ptEnd) const
{
	A=m_ptStart.y-m_ptEnd.y;
	B=m_ptEnd.x-m_ptStart.x;
	C=m_ptStart.x*m_ptEnd.y-m_ptEnd.x*m_ptStart.y;
}

void CPline::GetInterPoint(double A,double B,double C,double a,double b,double c,CPoint &pt)
{
	ASSERT( B*a-A*b != 0 );// 经过相交检查后该值肯定不为0
	pt.y=long((c*A-C*a)/(B*a-A*b));
	pt.x=long((c*B-C*b)/(A*b-B*a));
}

void CPline::DrawPar(CDC *pDC,CPoint &ParFlag)
{
		//if (ParFlag.y==0&&ParFlag.x==0) 
		//{
		//	AfxMessageBox("已经没有平行线可供删除");
		//	return;
		//}
		CPen pen;
		if (ParFlag.y==0) 
		{
			pen.CreatePen(4,1,RGB(255,255,255));
			ParFlag.x=0;
		}
		else 
		{
			pen.CreatePen(4,1,RGB(10,10,255));
			ParFlag.x=1;
		}
		CPen *pOldPen=pDC->SelectObject(&pen);
		CPoint *ppoint;  //创建一个点的数组指针

		ppoint=new CPoint[m_Number+1];//动态创建一个点的数组
		for(int i=0;i<m_Number;i++)//将顶点坐标转化成实际坐标,存放到ppoint中
		{	
			
			ppoint[i].x=m_PointList[i].x;   
			ppoint[i].y=m_PointList[i].y;
		}
		
			pDC->MoveTo(ppoint[0].x,ppoint[0].y);   //移动当前位置 
		for(i=1;i<m_Number;i++) 
		{
			pDC->LineTo(ppoint[i].x,ppoint[i].y);    //从当前位置到一点画直线，但不包括那个点 
		}
		delete  []ppoint;//删除原来动态分配的数组
		pDC->SelectObject(pOldPen);//恢复原来的画笔
		pen.DeleteObject();
}
