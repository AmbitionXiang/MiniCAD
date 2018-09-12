// LineView.cpp : implementation of the CLineView class
//

#include "stdafx.h"
#include "Line.h"

#include "LineDoc.h"
#include "LineView.h"
#include"Dlg.h"
#include"Dlg2.h"
#include<math.h>
#define PI 3.1415926


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define Max(A, B) ((A)>(B) ? (A) : (B))
#define Min(A, B) ((A)<(B) ? (A) : (B))

/////////////////////////////////////////////////////////////////////////////
// CLineView

IMPLEMENT_DYNCREATE(CLineView, CView)

BEGIN_MESSAGE_MAP(CLineView, CView)
	//{{AFX_MSG_MAP(CLineView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_LINE, OnLine)
	ON_COMMAND(ID_PAR, OnPar)
	ON_COMMAND(ID_CLEANPAR, OnCleanpar)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_INTERP, OnDrawCross)
	ON_COMMAND(ID_CLEANINTERP, OnCleanCross)
	ON_COMMAND(ID_ARC, OnArc)
	ON_COMMAND(ID_MULTILINE, OnMultiline)
	ON_COMMAND(ID_MULTISTART, OnMultistart)
	ON_COMMAND(ID_NEAR, OnNear)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineView construction/destruction

CLineView::CLineView()
{
	// TODO: add construction code here
	//m_PointList=new CPoint[1000];//申请数组空间
	m_nPushNum=0;//按下的次数初始值为0
	MultiNum=0;     //已画多义线的条数
	ArcFlag=0;   //画圆弧方式初始化
	ShowIPFlag=0;         //开始状态交点不可删除
	MultiStartFlag=FALSE;   //计算多义线起点与鼠标响应点距离的开关
	MultiNearFlag=FALSE;  //计算多义线与鼠标响应点最近距离的开关
	TPFlag=FALSE;        //默认下一点不是转点
	m_nLineStyle=0;
	m_nLineWidth=1;
	m_nLineColor=RGB(10,10,255);
	m_bType=FALSE;             //默认关闭画线模式
	m_MultiOpen=FALSE;         //默认关闭多义线模式
	ParFlag=CPoint(0,1);

}

CLineView::~CLineView()
{
}

BOOL CLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLineView drawing

void CLineView::OnDraw(CDC* pDC)
{
	CLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	
	pDoc->Draw(pDC);
	if(ParFlag.y==1)
	{
		pDoc->DrawPar(pDC,ParFlag);
	}
	if(ShowIPFlag==1)
	{
	OnDrawCross();
	}

	AfxMessageBox("界面刷新");


}

/////////////////////////////////////////////////////////////////////////////
// CLineView printing

BOOL CLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLineView diagnostics

#ifdef _DEBUG
void CLineView::AssertValid() const
{
	CView::AssertValid();
}

void CLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLineDoc* CLineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLineDoc)));
	return (CLineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLineView message handlers

void CLineView::OnLine() 
{
	// TODO: Add your command handler code here
	m_bType=1;
	m_PointList=new CPoint[1000];//申请数组空间
	
}

//判断两线段是否相交，存在一些问题
bool CLineView::IsIntersect(CPoint pFirst1, CPoint pFirst2, CPoint pSecond1, CPoint pSecond2)
{
	//每个线段的两点都在另一个线段的左右不同侧，则能断定线段相交
	//公式对于向量(x1,y1)->(x2,y2),判断点(x3,y3)在向量的左边,右边,还是线上.
	//p=x1(y3-y2)+x2(y1-y3)+x3(y2-y1).p<0 左侧,	p=0 线上, p>0 右侧
	long Linep1,Linep2;
	//判断pSecond1和pSecond2是否在pFirst1->pFirst2两侧
	Linep1 = pFirst1.x * (pSecond1.y - pFirst2.y) +
		pFirst2.x * (pFirst1.y - pSecond1.y) +
		pSecond1.x * (pFirst2.y - pFirst1.y);
	Linep2 = pFirst1.x * (pSecond2.y - pFirst2.y) +
		pFirst2.x * (pFirst1.y - pSecond2.y) +
		pSecond2.x * (pFirst2.y - pFirst1.y);
	if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//符号位异或为0:pSecond1和pSecond2在pFirst1->pFirst2同侧
	{
		return FALSE;
	}
	//判断pFirst1和pFirst2是否在pSecond1->pSecond2两侧
	Linep1 = pSecond1.x * (pFirst1.y - pSecond2.y) +
		pSecond2.x * (pSecond1.y - pFirst1.y) +
		pFirst1.x * (pSecond2.y - pSecond1.y);
	Linep2 = pSecond1.x * (pFirst2.y - pSecond2.y) +
		pSecond2.x * (pSecond1.y - pFirst2.y) +
		pFirst2.x * (pSecond2.y - pSecond1.y);
	if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//符号位异或为0:pFirst1和pFirst2在pSecond1->pSecond2同侧
	{
		return FALSE;
	}
	//否则判为相交
	return TRUE;
}

//画多边形的左侧平行线
void CLineView::DrawPar(CDC *pDC, CPoint *PointList, int Number,int t)      //画平行线（算法）
{
	PointList[Number]=PointList[0];	Number++; //加起点闭合

	CPoint *pts1=new CPoint[10000];
	int cnt1=0;
	double q1,q2,q,r;
	CPoint temp1,temp2,temp3;
	for(int i=0;i<Number;i++){
		temp1 = i==0? PointList[Number-2] : PointList[i-1];
		temp2 = PointList[i];
		temp3 = i<Number-1? PointList[i+1] : PointList[1];

		q1=atan2(temp2.y-temp3.y,temp2.x-temp3.x);
		q2=atan2(temp1.y-temp2.y,temp1.x-temp2.x);
		q=(q1+q2+PI)/2;
	
		r=t/(cos((q1-q2)/2));	//求出对角线出所对应的圆的半径
		pts1[cnt1].x=(long)(temp2.x+r*cos(q)+0.5);
		pts1[cnt1].y=(long)(temp2.y+r*sin(q)+0.5);
		cnt1++;
	}
	
	//画出左侧平行线
    CClientDC dc(this);//////
	CPen pen(4,1,RGB(10,10,255));//////设置平行线专有的格式
	CPen *pOldPen=dc.SelectObject(&pen);//////
	pDC=&dc;                            //////
	CLineDoc *pDoc=GetDocument();
	pDC->MoveTo(pts1[0].x,pts1[0].y);
	for(i=1;i<cnt1;i++) pDC->LineTo(pts1[i].x,pts1[i].y);
	pDoc->AddParPline(Number,pts1);            //存储平行线//////
	delete pts1;
	dc.SelectObject(pOldPen);
	pen.DeleteObject();
}


void CLineView::ChangePen(CPen &pen,int type,int width,COLORREF color)
{
	LOGPEN lopn;
	switch(type)
	{
	case 0:lopn.lopnStyle=PS_SOLID;lopn.lopnWidth.x=width;break;
	case 1:lopn.lopnStyle=PS_DOT;lopn.lopnWidth.x=1;break;
	case 2:lopn.lopnStyle=PS_DASH;lopn.lopnWidth.x=1;break;
	case 3:lopn.lopnStyle=PS_DASHDOT;lopn.lopnWidth.x=1;break;
	}
	lopn.lopnColor=color;
	pen.CreatePenIndirect(&lopn);     
}

void CLineView::OnPar()                                         //菜单中选择画平行线
{
	// TODO: Add your command handler code here
	CLineDoc *pDoc=GetDocument();
	CClientDC dc(this);
	ParFlag.x=1;
	ParFlag.y=1;
	dlg.DoModal();
	int t=dlg.m_nDis;       //平行线间距
	int nn=pDoc->m_PLineArray.GetUpperBound()+1;//得到存储第i类图形元素对象指针数组的最大下标
	int nm=pDoc->m_PLineArray.GetAt(0)->GetNumber();
		CString str,str1;
//		str.Format("%d",nn);
//		str1.Format("%d",nm);
//		AfxMessageBox(str+"\t"+str1);
	while(nn--)
	{
		DrawPar(&dc,pDoc->m_PLineArray.GetAt(nn)->GetPList(),pDoc->m_PLineArray.GetAt(nn)->GetNumber(),t);
	}
	
	
}

void CLineView::OnCleanpar() 
{
	// TODO: Add your command handler code here
		ParFlag.y=0;
		CClientDC dc(this);
		CLineDoc *pDoc=GetDocument();
		CPen pen(4,1,RGB(255,255,255));
		CPen *pOldPen=dc.SelectObject(&pen);
		int nn=pDoc->m_ParPLineArray.GetUpperBound()+1;//得到存储第i类图形元素对象指针数组的最大下标
		while(nn--)
		{
			pDoc->m_ParPLineArray.GetAt(nn)->DrawPar(&dc,ParFlag);
		}
		dc.SelectObject(pOldPen);
		pen.DeleteObject();
}

void CLineView::OnFileNew() 
{
	// TODO: Add your command handler code here
	CLineDoc *pDoc=GetDocument();
	pDoc->m_PLineArray.RemoveAll();
	pDoc->m_ParPLineArray.RemoveAll();
	delete pDoc->InterPList;
	pDoc->InterPNum=0;
	Invalidate();
}

void CLineView::OnDrawCross() 
{
	// TODO: Add your command handler code here
	ShowIPFlag=1;
	CPen pen(PS_SOLID,1,RGB(255,0,0)),*pOldPen;
	CLineDoc *pDoc=GetDocument();
	CClientDC dc(this);
	int cx=4,cy=4;
	pOldPen=dc.SelectObject(&pen);
	CPoint * IPList=pDoc->InterPList;
	int Num=pDoc->InterPNum;
	for(int i=0;i<Num;i++)
	{
		dc.MoveTo((int)IPList[i].x-cx,(int)IPList[i].y-cy);
		dc.LineTo((int)IPList[i].x+cx+1,(int)IPList[i].y+cy+1);
		dc.MoveTo((int)IPList[i].x-cx,(int)IPList[i].y+cy);
		dc.LineTo((int)IPList[i].x+cx+1,(int)IPList[i].y-cy-1);
	}
	dc.SelectObject(pOldPen);
	pen.DeleteObject();
}


void CLineView::OnCleanCross() 
{
	// TODO: Add your command handler code here
	ShowIPFlag=0;
	CPen pen(PS_SOLID,1,RGB(255,255,255)),*pOldPen;
	CLineDoc *pDoc=GetDocument();
	CClientDC dc(this);
	int cx=4,cy=4;
	pOldPen=dc.SelectObject(&pen);
	CPoint * IPList=pDoc->InterPList;
	int Num=pDoc->InterPNum;
	for(int i=0;i<Num;i++)
	{
		dc.MoveTo((int)IPList[i].x-cx,(int)IPList[i].y-cy);
		dc.LineTo((int)IPList[i].x+cx+1,(int)IPList[i].y+cy+1);
		dc.MoveTo((int)IPList[i].x-cx,(int)IPList[i].y+cy);
		dc.LineTo((int)IPList[i].x+cx+1,(int)IPList[i].y-cy-1);
	}
	dc.SelectObject(pOldPen);
	pen.DeleteObject();
}

void CLineView::OnArc() 
{
	// TODO: Add your command handler code here
	m_bType=2;
	m_PointList=new CPoint[1000];//申请数组空间
}

void CLineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(MultiStartFlag==TRUE)
	{
		CClientDC dc(this);
		int cx=4,cy=4;
		dc.MoveTo((int)point.x-cx,(int)point.y-cy);
		dc.LineTo((int)point.x+cx+1,(int)point.y+cy+1);
		dc.MoveTo((int)point.x-cx,(int)point.y+cy);
		dc.LineTo((int)point.x+cx+1,(int)point.y-cy-1);
		Distance=pow((pow(MultiStart[dlg5.m_Edit2-1].x-point.x,2)+pow(MultiStart[dlg5.m_Edit2-1].y-point.y,2)),0.5);
		CString str;
		str.Format("鼠标响应点到第%d条多义线的起点的距离为%7.2f单位（保留两位小数）",dlg5.m_Edit2,Distance); //显示距离
		AfxMessageBox(str);
		MultiStartFlag=FALSE;
		return;
	}
	if(MultiNearFlag==TRUE)
	{
		CLineDoc *pDoc=GetDocument();//获取当前文档
		CClientDC dc(this);
		int cx=4,cy=4;
		double A,B,C,minD=100000,Distance;
		CPline *pPline=pDoc->m_PLineArray.GetAt(Multi[dlg6.m_Edit1-1][1]);
		dc.MoveTo((int)point.x-cx,(int)point.y-cy);
		dc.LineTo((int)point.x+cx+1,(int)point.y+cy+1);
		dc.MoveTo((int)point.x-cx,(int)point.y+cy);
		dc.LineTo((int)point.x+cx+1,(int)point.y-cy-1);
		for(int k=0;k<pPline->GetNumber();k++)
		{
			pPline->GetParam(A,B,C,pPline->GetPList()[k],pPline->GetPList()[k+1]);
			Distance=fabs((A*point.x+B*point.y+C)/(sqrt(A*A+B*B)));
			if(Distance<minD) minD=Distance;
		}
		CString str;
		str.Format("鼠标响应点到第%d条多义线的最短距离为%7.2f单位（保留两位小数）",dlg6.m_Edit1,minD); //显示距离
		AfxMessageBox(str);
		MultiNearFlag=FALSE;
		return;
	}

	if(m_bType)
	{	
		CLineDoc *pDoc=GetDocument();//获取当前文档
		CClientDC dc(this);
		//定义并获取画笔
		CPline *pPline;
		if (m_nPushNum==0)    
		{
			dlg2.DoModal(); //请选择画笔模式
		}
		if (m_nPushNum==0&&m_MultiOpen==TRUE)
		{
			dlg4.DoModal();
			if(dlg4.m_radio==0)
				m_bType=1;
			else
			{
				m_bType=2;
				if(dlg4.m_radio==1)
					ArcFlag=1;
				else
				{
					ArcFlag=dlg4.m_radio;   //选定画弧方式
					TPFlag=FALSE;
				}
				if(ArcFlag==3)
				{
					AfxMessageBox("第一条圆弧不能以切线形式画出");
					m_MultiOpen=FALSE;  //关闭多义线模式
					ArcFlag=0;         //画圆弧方式初始化
					m_bType=0;         //关闭画线模式
					delete []m_PointList;
					m_PointList=NULL;
					OnDraw(&dc);   //刷新页面
					return;
				}
			}
			MultiStart[MultiNum]=point;
			Multi[MultiNum][0]=MultiNum+1;    //记录多义线为第MultiNum+1条
			Multi[MultiNum][1]=pDoc->m_PLineArray.GetUpperBound()+1; //第MultiNum+1条多义线在所有连续线组中的索引值
			MultiNum++;  //已画多义线条数+1
		}
		if (m_MultiOpen==FALSE&&m_nPushNum==0&&m_bType==2)
		{
			dlg3.DoModal();   //输入圆心角
			ArcFlag=dlg3.m_ArcType+1;
		}
		AutoShowPar=dlg2.m_AutoShowPar;        //是否自动显示平行线                        //////
		ChangePen(pen,dlg2.m_TypeIndex,dlg2.m_Width,RGB(dlg2.m_Color1,dlg2.m_Color2,dlg2.m_Color3));//////
		pOldPen=dc.SelectObject(&pen);
		if(!TPFlag)
		{
			/////////////////////////////////////////////////////////
			//判断所画折线是否相交,如相交则记录交点
			int nn=pDoc->m_PLineArray.GetUpperBound()+1; 
			if(m_bType==1)
			{
				for(int i=0;i<m_nPushNum-2;i++)
				{	
					if(IsIntersect(m_PointList[i],m_PointList[i+1],m_PointList[m_nPushNum-1],point)==TRUE)
					{
						//CString str;
						//str.Format("%d",m_nPushNum-1);
						//AfxMessageBox(str);
						pPline->GetParam(A,B,C,m_PointList[m_nPushNum-1],point);
						pPline->GetParam(a,b,c,m_PointList[i],m_PointList[i+1]);
						pPline->GetInterPoint(A,B,C,a,b,c,pDoc->InterPList[pDoc->InterPNum++]);
					}
				}	
				while(nn--)
				{
					pPline=pDoc->m_PLineArray.GetAt(nn);
					if(m_nPushNum!=0)
					for(int i=0;i<pPline->GetNumber()-1;i++)
					{	
						if(IsIntersect(pPline->GetPList()[i],pPline->GetPList()[i+1],m_PointList[m_nPushNum-1],point)==TRUE)
						{
							pPline->GetParam(A,B,C,m_PointList[m_nPushNum-1],point);
							pPline->GetParam(a,b,c,pPline->GetPList()[i],pPline->GetPList()[i+1]);
							pPline->GetInterPoint(A,B,C,a,b,c,pDoc->InterPList[pDoc->InterPNum++]);
						}		
					}
				}
			}
			if(m_bType==2)
			{	
				int TempNum,flag=0;//默认不相交
				for(int i=0;i<m_nPushNum-2;i++)
				{	
					TempNum=1;
					while(!(IsIntersect(m_PointList[i],m_PointList[i+1],Arc.PointList[TempNum-1],Arc.PointList[TempNum])==TRUE))
					{
						TempNum++;
						if (TempNum>Arc.part)	break;
					}
					if(TempNum<=Arc.part)
					{
						flag=1;
						pPline->GetParam(A,B,C,Arc.PointList[TempNum-1],Arc.PointList[TempNum]);
						pPline->GetParam(a,b,c,m_PointList[i],m_PointList[i+1]);
						pPline->GetInterPoint(A,B,C,a,b,c,pDoc->InterPList[pDoc->InterPNum++]);
					}
				}
				if(!flag)    //未找到交点
				{
					while(nn--)
					{
						pPline=pDoc->m_PLineArray.GetAt(nn);
						if(m_nPushNum!=0)
						for(int i=0;i<pPline->GetNumber()-1;i++)
						{	
							TempNum=1;
							while(!(IsIntersect(pPline->GetPList()[i],pPline->GetPList()[i+1],Arc.PointList[TempNum-1],Arc.PointList[TempNum])==TRUE))
							{
								TempNum++;
								if (TempNum>Arc.part)	break;
							}
							if(TempNum<=Arc.part)
							{
								flag=1;
								pPline->GetParam(A,B,C,Arc.PointList[TempNum-1],Arc.PointList[TempNum]);
								pPline->GetParam(a,b,c,pPline->GetPList()[i],pPline->GetPList()[i+1]);
								pPline->GetInterPoint(A,B,C,a,b,c,pDoc->InterPList[pDoc->InterPNum++]);
							}	
						}
					}
				}
			}
				//设置当前的光标为十字光标
			SetCursor(LoadCursor(NULL,IDC_CROSS));
			if(m_nPushNum==0)//第一次按下鼠标
			{
				SetCapture();
				if(m_MultiOpen==TRUE)
					Arc.DM_Angle=dlg4.m_Angle;
				else
					Arc.DM_Angle=dlg3.m_DlgAngle;
				Arc.m_Start=m_ptOrigin=point;
				Arc.m_Finish=m_ptOldPoint=point;
				Arc.ArcCalc(m_ptOrigin,m_ptOldPoint);
				m_PointList[m_nPushNum].x=point.x;
				m_PointList[m_nPushNum].y=point.y;
				m_nPushNum++;//记录鼠标按下左键的次数
				if(m_bType==2&&ArcFlag==1)                      //若选择三点画弧模式标出第一个点
				{
					int cx=4,cy=4;
					dc.MoveTo((int)point.x-cx,(int)point.y-cy);
					dc.LineTo((int)point.x+cx+1,(int)point.y+cy+1);
					dc.MoveTo((int)point.x-cx,(int)point.y+cy);
					dc.LineTo((int)point.x+cx+1,(int)point.y-cy-1);
				}
				ReleaseCapture();
			}
			else//第二次或以上按下鼠标左键
			{	
				SetCapture();
				Arc.m_Start=m_ptOrigin;
				m_ptOrigin=m_ptOldPoint;//设上一个点为坐标原点
				m_ptOldPoint=point;//将鼠标按中点作为鼠标移动时的上一个移动点
				Arc.ArcCalc(Arc.m_Start,Arc.m_Finish);
					//获取鼠标按下的点
				if(m_bType==1||(m_nPushNum==1&&m_bType==2&&ArcFlag==3))
				{
					m_PointList[m_nPushNum].x=point.x;
					m_PointList[m_nPushNum].y=point.y;
					m_nPushNum++;//记录鼠标按下左键的次数
				}
				else if(m_bType==2)
				{
					for(int j=1;j<Arc.part+1;j++)
					{
						m_PointList[m_nPushNum].x=Arc.PointList[j].x;
						m_PointList[m_nPushNum].y=Arc.PointList[j].y;
						m_nPushNum++;
					}
					Arc.ArcCalc(m_ptOrigin,m_ptOldPoint);
				}
				ReleaseCapture();
	
			}
		
			SetCursor(LoadCursor(NULL,IDC_ARROW)); 
			if (m_nPushNum>1&&m_MultiOpen==TRUE)   //多义线模式下每画一条前都要进行选择
			{
				if(dlg4.DoModal()==IDOK)
				if(dlg4.m_radio==0)
					m_bType=1;
				else
				{
					m_bType=2;
					if(dlg4.m_radio==1)
						ArcFlag=1;
					else
					{
						ArcFlag=dlg4.m_radio;    //选定画弧模式
						TPFlag=FALSE;
					}
				}
			}
			if (m_bType==2&&ArcFlag==1)
			{
				TPFlag=TRUE;//下一个点击为转点
			}
		}
		else
		{
			Arc.m_Turn=point;             //记录转点
			int cx=4,cy=4;
			dc.MoveTo((int)point.x-cx,(int)point.y-cy);
			dc.LineTo((int)point.x+cx+1,(int)point.y+cy+1);
			dc.MoveTo((int)point.x-cx,(int)point.y+cy);
			dc.LineTo((int)point.x+cx+1,(int)point.y-cy-1);
			TPFlag=FALSE;
		}
		dc.SelectObject(pOldPen);               //还原画笔
		pen.DeleteObject();	
	}
	CView::OnLButtonDown(nFlags, point);    //系统默认添加按下左键的响应内容，没有实际用处。
}

void CLineView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!IsWindow(dlg4)) 
	{
		CClientDC dc(this);
		if(m_bType&&m_nPushNum>0)
		{
			if(m_ptOldPoint!=point)
			{
				if (m_bType==1||(m_nPushNum==1&&m_bType==2&&ArcFlag==3))
				{
					ChangePen(pen,dlg2.m_TypeIndex,dlg2.m_Width,RGB(255,255,255));   //擦除
					pOldPen=dc.SelectObject(&pen);
					dc.MoveTo(m_ptOrigin);
					dc.LineTo(m_ptOldPoint);//擦除上一条直线（反色）
					dc.SelectObject(pOldPen);
					pen.DeleteObject();
					
					ChangePen(pen,dlg2.m_TypeIndex,dlg2.m_Width,RGB(dlg2.m_Color1,dlg2.m_Color2,dlg2.m_Color3));
					pOldPen=dc.SelectObject(&pen);
					dc.MoveTo(m_ptOrigin);
					dc.LineTo(point);//绘制鼠标起点到鼠标移动点的连线
					Arc.m_Finish=m_ptOldPoint=point;//将当前的鼠标点记录为下次操作的上一个移动点
					dc.SelectObject(pOldPen);
					pen.DeleteObject();
				}
				else if(m_bType==2)
				{
					if(ArcFlag>1||ArcFlag==1&&TPFlag==FALSE)
					{
						if (Arc.PointList!=NULL)                                   
						{	
							ChangePen(pen,dlg2.m_TypeIndex,dlg2.m_Width,RGB(255,255,255));
							pOldPen=dc.SelectObject(&pen);
							dc.MoveTo(m_ptOrigin);								
							for(int j=1;j<Arc.part+1;j++)
								dc.LineTo(Arc.PointList[j]);
							delete []Arc.PointList;
							Arc.PointList=NULL;
							dc.SelectObject(pOldPen);
							pen.DeleteObject();
						}
						ChangePen(pen,dlg2.m_TypeIndex,dlg2.m_Width,RGB(dlg2.m_Color1,dlg2.m_Color2,dlg2.m_Color3));
						pOldPen=dc.SelectObject(&pen);
						dc.MoveTo(m_ptOrigin);
						Arc.m_Finish=m_ptOldPoint=point;
						if(ArcFlag==1&&TPFlag==FALSE)
						{
							Arc.GetCircleAngle(m_ptOrigin,Arc.m_Turn,m_ptOldPoint,Arc.DM_Angle);
							//CString str,str1,str2,str3;
							//str.Format("%d  %d ",m_ptOrigin.x,m_ptOrigin.y);
							//str1.Format("%d %d ",Arc.m_Turn.x,Arc.m_Turn.y);
							//str2.Format("%d %d ",m_ptOldPoint.x,m_ptOldPoint.y);
							//str3.Format("%7.2f",Arc.DM_Angle);
							//AfxMessageBox(str+" "+str1+" "+str2+" "+str3);
						}
						if(ArcFlag==3)
						{
							double brangle1=Arc.GetBrAngle(m_ptOrigin,m_ptOldPoint),brangle2=Arc.GetBrAngle(m_PointList[m_nPushNum-2],m_PointList[m_nPushNum-1]);
							while (brangle1<brangle2)
								brangle1+=2*PI;
							Arc.DM_Angle=2*(brangle1-brangle2)/PI*180;
						}

						Arc.ArcCalc(m_ptOrigin,m_ptOldPoint);

						
						for(int j=1;j<Arc.part+1;j++)
							dc.LineTo(Arc.PointList[j]);
						dc.SelectObject(pOldPen);
						pen.DeleteObject();
					}
				}
					
			}
		}
		CView::OnMouseMove(nFlags, point);
	}
}


void CLineView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CLineDoc *pDoc=GetDocument();
	CClientDC dc(this);
	//擦除上一条拖动的橡皮线
	if(m_bType&&m_nPushNum>0)
	{
		ChangePen(pen,dlg2.m_TypeIndex,dlg2.m_Width,RGB(255,255,255));//////												//////请选择画笔样式
		pOldPen=dc.SelectObject(&pen);    //////
		if(m_bType==1)
		{
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(m_ptOldPoint);
		}
		else if(m_bType==2)
		{
			dc.MoveTo(m_ptOrigin);
			for(int j=1;j<Arc.part+1;j++)
				dc.LineTo(Arc.PointList[j]);
		}
		dc.SelectObject(pOldPen);               //还原画笔//////
		pen.DeleteObject();
		pDoc->AddPline(m_nPushNum,m_PointList,dlg2.m_TypeIndex,dlg2.m_Width,RGB(dlg2.m_Color1,dlg2.m_Color2,dlg2.m_Color3)); //保存连续线和对应线条类型
		ReleaseCapture();//释放捕捉的鼠标	
		m_bType=0;//将画线模式置为FALSE
		if(AutoShowPar)                     //////
		{
			dlg.DoModal();
			int t=dlg.m_nDis;       //平行线间距
			DrawPar(&dc,m_PointList,m_nPushNum,t);
		}
		m_MultiOpen=FALSE;  //关闭多义线模式
		ArcFlag=0;         //画圆弧方式初始化
		TPFlag=FALSE;   //转点标记关闭
		m_nPushNum=0;//按下鼠标次数设为0
		delete []Arc.PointList;
		Arc.PointList=NULL;
		delete []m_PointList;
		m_PointList=NULL;
		OnDraw(&dc);   //刷新页面

		

		
	}
//	ReleaseCapture();//释放捕捉鼠标
	CView::OnRButtonDown(nFlags, point);    //系统默认添加
}

void CLineView::OnMultiline()                  //开启多义线模式
{
	// TODO: Add your command handler code here
	m_bType=3;
	m_MultiOpen=TRUE;
	m_PointList=new CPoint[1000];//申请数组空间
}

void CLineView::OnMultistart()                  //开启计算起点距离模式
{
	// TODO: Add your command handler code here
	MultiStartFlag=TRUE;
	if(MultiNum==0)
	{
		AfxMessageBox("当前没有画多义线，操作无效");
		return;
	}
	dlg5.DoModal();
}

void CLineView::OnNear()                     //开启计算最近距离模式
{
	// TODO: Add your command handler code here
	MultiNearFlag=TRUE;
	if(MultiNum==0)
	{
		AfxMessageBox("当前没有画多义线，操作无效");
		return;
	}
	dlg6.DoModal();

}
