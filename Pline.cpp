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
	m_PointList=NULL;//��ʼ���ö�������ΪNULL
	
}

CPline::~CPline()
{

}

void CPline::Draw(CDC *pDC,int n)
{ 
	CPen *pOldPen=pDC->SelectObject(&pen[n]);
	/*i. Ҫʹ������Ч�ͱ����Ƚ������õ�CPen����ѡ��dc�豸�����У�
ii. ʹ��SelectObject����ͼ����ѡ�뻷���豸dc�У�CPen* SelectObject(CPen* pPen);���䷵�ظ���֮ǰ���ϻ��ʵľ����
iii. MFC��SelectObject���ع��ü����汾�ģ���CBrush���������͵Ļ�ͼ��������ֻ�ǻ���һ�ֶ��ѣ�
iv. CPen* pOldPen = dc.SelectObject(pNewPen);*/

	CPoint *ppoint;  //����һ���������ָ��

	ppoint=new CPoint[m_Number+1];//��̬����һ���������
	for(int i=0;i<m_Number;i++)//����������ת����ʵ������,��ŵ�ppoint��
	{	
		
		ppoint[i].x=m_PointList[i].x;   
		ppoint[i].y=m_PointList[i].y;
	}
	
		pDC->MoveTo(ppoint[0].x,ppoint[0].y);   //�ƶ���ǰλ�� 
	for(i=1;i<m_Number;i++) 
	{
		pDC->LineTo(ppoint[i].x,ppoint[i].y);    //�ӵ�ǰλ�õ�һ�㻭ֱ�ߣ����������Ǹ��� 
	}
	delete  []ppoint;//ɾ��ԭ����̬���������
	pDC->SelectObject(pOldPen);//�ָ�ԭ���Ļ���
	//pen[n].DeleteObject();
	
}

CPline::CPline(int Number,CPoint *PointList)
{
	m_Number=Number;

	m_PointList=new CPoint[Number+1];//��̬����ռ�
	
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
	ASSERT( B*a-A*b != 0 );// �����ཻ�����ֵ�϶���Ϊ0
	pt.y=long((c*A-C*a)/(B*a-A*b));
	pt.x=long((c*B-C*b)/(A*b-B*a));
}

void CPline::DrawPar(CDC *pDC,CPoint &ParFlag)
{
		//if (ParFlag.y==0&&ParFlag.x==0) 
		//{
		//	AfxMessageBox("�Ѿ�û��ƽ���߿ɹ�ɾ��");
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
		CPoint *ppoint;  //����һ���������ָ��

		ppoint=new CPoint[m_Number+1];//��̬����һ���������
		for(int i=0;i<m_Number;i++)//����������ת����ʵ������,��ŵ�ppoint��
		{	
			
			ppoint[i].x=m_PointList[i].x;   
			ppoint[i].y=m_PointList[i].y;
		}
		
			pDC->MoveTo(ppoint[0].x,ppoint[0].y);   //�ƶ���ǰλ�� 
		for(i=1;i<m_Number;i++) 
		{
			pDC->LineTo(ppoint[i].x,ppoint[i].y);    //�ӵ�ǰλ�õ�һ�㻭ֱ�ߣ����������Ǹ��� 
		}
		delete  []ppoint;//ɾ��ԭ����̬���������
		pDC->SelectObject(pOldPen);//�ָ�ԭ���Ļ���
		pen.DeleteObject();
}
