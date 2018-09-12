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
	//m_PointList=new CPoint[1000];//��������ռ�
	m_nPushNum=0;//���µĴ�����ʼֵΪ0
	MultiNum=0;     //�ѻ������ߵ�����
	ArcFlag=0;   //��Բ����ʽ��ʼ��
	ShowIPFlag=0;         //��ʼ״̬���㲻��ɾ��
	MultiStartFlag=FALSE;   //�������������������Ӧ�����Ŀ���
	MultiNearFlag=FALSE;  //����������������Ӧ���������Ŀ���
	TPFlag=FALSE;        //Ĭ����һ�㲻��ת��
	m_nLineStyle=0;
	m_nLineWidth=1;
	m_nLineColor=RGB(10,10,255);
	m_bType=FALSE;             //Ĭ�Ϲرջ���ģʽ
	m_MultiOpen=FALSE;         //Ĭ�Ϲرն�����ģʽ
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

	AfxMessageBox("����ˢ��");


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
	m_PointList=new CPoint[1000];//��������ռ�
	
}

//�ж����߶��Ƿ��ཻ������һЩ����
bool CLineView::IsIntersect(CPoint pFirst1, CPoint pFirst2, CPoint pSecond1, CPoint pSecond2)
{
	//ÿ���߶ε����㶼����һ���߶ε����Ҳ�ͬ�࣬���ܶ϶��߶��ཻ
	//��ʽ��������(x1,y1)->(x2,y2),�жϵ�(x3,y3)�����������,�ұ�,��������.
	//p=x1(y3-y2)+x2(y1-y3)+x3(y2-y1).p<0 ���,	p=0 ����, p>0 �Ҳ�
	long Linep1,Linep2;
	//�ж�pSecond1��pSecond2�Ƿ���pFirst1->pFirst2����
	Linep1 = pFirst1.x * (pSecond1.y - pFirst2.y) +
		pFirst2.x * (pFirst1.y - pSecond1.y) +
		pSecond1.x * (pFirst2.y - pFirst1.y);
	Linep2 = pFirst1.x * (pSecond2.y - pFirst2.y) +
		pFirst2.x * (pFirst1.y - pSecond2.y) +
		pSecond2.x * (pFirst2.y - pFirst1.y);
	if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//����λ���Ϊ0:pSecond1��pSecond2��pFirst1->pFirst2ͬ��
	{
		return FALSE;
	}
	//�ж�pFirst1��pFirst2�Ƿ���pSecond1->pSecond2����
	Linep1 = pSecond1.x * (pFirst1.y - pSecond2.y) +
		pSecond2.x * (pSecond1.y - pFirst1.y) +
		pFirst1.x * (pSecond2.y - pSecond1.y);
	Linep2 = pSecond1.x * (pFirst2.y - pSecond2.y) +
		pSecond2.x * (pSecond1.y - pFirst2.y) +
		pFirst2.x * (pSecond2.y - pSecond1.y);
	if ( ((Linep1 ^ Linep2) >= 0 ) && !(Linep1==0 && Linep2==0))//����λ���Ϊ0:pFirst1��pFirst2��pSecond1->pSecond2ͬ��
	{
		return FALSE;
	}
	//������Ϊ�ཻ
	return TRUE;
}

//������ε����ƽ����
void CLineView::DrawPar(CDC *pDC, CPoint *PointList, int Number,int t)      //��ƽ���ߣ��㷨��
{
	PointList[Number]=PointList[0];	Number++; //�����պ�

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
	
		r=t/(cos((q1-q2)/2));	//����Խ��߳�����Ӧ��Բ�İ뾶
		pts1[cnt1].x=(long)(temp2.x+r*cos(q)+0.5);
		pts1[cnt1].y=(long)(temp2.y+r*sin(q)+0.5);
		cnt1++;
	}
	
	//�������ƽ����
    CClientDC dc(this);//////
	CPen pen(4,1,RGB(10,10,255));//////����ƽ����ר�еĸ�ʽ
	CPen *pOldPen=dc.SelectObject(&pen);//////
	pDC=&dc;                            //////
	CLineDoc *pDoc=GetDocument();
	pDC->MoveTo(pts1[0].x,pts1[0].y);
	for(i=1;i<cnt1;i++) pDC->LineTo(pts1[i].x,pts1[i].y);
	pDoc->AddParPline(Number,pts1);            //�洢ƽ����//////
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

void CLineView::OnPar()                                         //�˵���ѡ��ƽ����
{
	// TODO: Add your command handler code here
	CLineDoc *pDoc=GetDocument();
	CClientDC dc(this);
	ParFlag.x=1;
	ParFlag.y=1;
	dlg.DoModal();
	int t=dlg.m_nDis;       //ƽ���߼��
	int nn=pDoc->m_PLineArray.GetUpperBound()+1;//�õ��洢��i��ͼ��Ԫ�ض���ָ�����������±�
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
		int nn=pDoc->m_ParPLineArray.GetUpperBound()+1;//�õ��洢��i��ͼ��Ԫ�ض���ָ�����������±�
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
	m_PointList=new CPoint[1000];//��������ռ�
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
		str.Format("�����Ӧ�㵽��%d�������ߵ����ľ���Ϊ%7.2f��λ��������λС����",dlg5.m_Edit2,Distance); //��ʾ����
		AfxMessageBox(str);
		MultiStartFlag=FALSE;
		return;
	}
	if(MultiNearFlag==TRUE)
	{
		CLineDoc *pDoc=GetDocument();//��ȡ��ǰ�ĵ�
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
		str.Format("�����Ӧ�㵽��%d�������ߵ���̾���Ϊ%7.2f��λ��������λС����",dlg6.m_Edit1,minD); //��ʾ����
		AfxMessageBox(str);
		MultiNearFlag=FALSE;
		return;
	}

	if(m_bType)
	{	
		CLineDoc *pDoc=GetDocument();//��ȡ��ǰ�ĵ�
		CClientDC dc(this);
		//���岢��ȡ����
		CPline *pPline;
		if (m_nPushNum==0)    
		{
			dlg2.DoModal(); //��ѡ�񻭱�ģʽ
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
					ArcFlag=dlg4.m_radio;   //ѡ��������ʽ
					TPFlag=FALSE;
				}
				if(ArcFlag==3)
				{
					AfxMessageBox("��һ��Բ��������������ʽ����");
					m_MultiOpen=FALSE;  //�رն�����ģʽ
					ArcFlag=0;         //��Բ����ʽ��ʼ��
					m_bType=0;         //�رջ���ģʽ
					delete []m_PointList;
					m_PointList=NULL;
					OnDraw(&dc);   //ˢ��ҳ��
					return;
				}
			}
			MultiStart[MultiNum]=point;
			Multi[MultiNum][0]=MultiNum+1;    //��¼������Ϊ��MultiNum+1��
			Multi[MultiNum][1]=pDoc->m_PLineArray.GetUpperBound()+1; //��MultiNum+1�����������������������е�����ֵ
			MultiNum++;  //�ѻ�����������+1
		}
		if (m_MultiOpen==FALSE&&m_nPushNum==0&&m_bType==2)
		{
			dlg3.DoModal();   //����Բ�Ľ�
			ArcFlag=dlg3.m_ArcType+1;
		}
		AutoShowPar=dlg2.m_AutoShowPar;        //�Ƿ��Զ���ʾƽ����                        //////
		ChangePen(pen,dlg2.m_TypeIndex,dlg2.m_Width,RGB(dlg2.m_Color1,dlg2.m_Color2,dlg2.m_Color3));//////
		pOldPen=dc.SelectObject(&pen);
		if(!TPFlag)
		{
			/////////////////////////////////////////////////////////
			//�ж����������Ƿ��ཻ,���ཻ���¼����
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
				int TempNum,flag=0;//Ĭ�ϲ��ཻ
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
				if(!flag)    //δ�ҵ�����
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
				//���õ�ǰ�Ĺ��Ϊʮ�ֹ��
			SetCursor(LoadCursor(NULL,IDC_CROSS));
			if(m_nPushNum==0)//��һ�ΰ������
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
				m_nPushNum++;//��¼��갴������Ĵ���
				if(m_bType==2&&ArcFlag==1)                      //��ѡ�����㻭��ģʽ�����һ����
				{
					int cx=4,cy=4;
					dc.MoveTo((int)point.x-cx,(int)point.y-cy);
					dc.LineTo((int)point.x+cx+1,(int)point.y+cy+1);
					dc.MoveTo((int)point.x-cx,(int)point.y+cy);
					dc.LineTo((int)point.x+cx+1,(int)point.y-cy-1);
				}
				ReleaseCapture();
			}
			else//�ڶ��λ����ϰ���������
			{	
				SetCapture();
				Arc.m_Start=m_ptOrigin;
				m_ptOrigin=m_ptOldPoint;//����һ����Ϊ����ԭ��
				m_ptOldPoint=point;//����갴�е���Ϊ����ƶ�ʱ����һ���ƶ���
				Arc.ArcCalc(Arc.m_Start,Arc.m_Finish);
					//��ȡ��갴�µĵ�
				if(m_bType==1||(m_nPushNum==1&&m_bType==2&&ArcFlag==3))
				{
					m_PointList[m_nPushNum].x=point.x;
					m_PointList[m_nPushNum].y=point.y;
					m_nPushNum++;//��¼��갴������Ĵ���
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
			if (m_nPushNum>1&&m_MultiOpen==TRUE)   //������ģʽ��ÿ��һ��ǰ��Ҫ����ѡ��
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
						ArcFlag=dlg4.m_radio;    //ѡ������ģʽ
						TPFlag=FALSE;
					}
				}
			}
			if (m_bType==2&&ArcFlag==1)
			{
				TPFlag=TRUE;//��һ�����Ϊת��
			}
		}
		else
		{
			Arc.m_Turn=point;             //��¼ת��
			int cx=4,cy=4;
			dc.MoveTo((int)point.x-cx,(int)point.y-cy);
			dc.LineTo((int)point.x+cx+1,(int)point.y+cy+1);
			dc.MoveTo((int)point.x-cx,(int)point.y+cy);
			dc.LineTo((int)point.x+cx+1,(int)point.y-cy-1);
			TPFlag=FALSE;
		}
		dc.SelectObject(pOldPen);               //��ԭ����
		pen.DeleteObject();	
	}
	CView::OnLButtonDown(nFlags, point);    //ϵͳĬ����Ӱ����������Ӧ���ݣ�û��ʵ���ô���
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
					ChangePen(pen,dlg2.m_TypeIndex,dlg2.m_Width,RGB(255,255,255));   //����
					pOldPen=dc.SelectObject(&pen);
					dc.MoveTo(m_ptOrigin);
					dc.LineTo(m_ptOldPoint);//������һ��ֱ�ߣ���ɫ��
					dc.SelectObject(pOldPen);
					pen.DeleteObject();
					
					ChangePen(pen,dlg2.m_TypeIndex,dlg2.m_Width,RGB(dlg2.m_Color1,dlg2.m_Color2,dlg2.m_Color3));
					pOldPen=dc.SelectObject(&pen);
					dc.MoveTo(m_ptOrigin);
					dc.LineTo(point);//���������㵽����ƶ��������
					Arc.m_Finish=m_ptOldPoint=point;//����ǰ�������¼Ϊ�´β�������һ���ƶ���
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
	//������һ���϶�����Ƥ��
	if(m_bType&&m_nPushNum>0)
	{
		ChangePen(pen,dlg2.m_TypeIndex,dlg2.m_Width,RGB(255,255,255));//////												//////��ѡ�񻭱���ʽ
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
		dc.SelectObject(pOldPen);               //��ԭ����//////
		pen.DeleteObject();
		pDoc->AddPline(m_nPushNum,m_PointList,dlg2.m_TypeIndex,dlg2.m_Width,RGB(dlg2.m_Color1,dlg2.m_Color2,dlg2.m_Color3)); //���������ߺͶ�Ӧ��������
		ReleaseCapture();//�ͷŲ�׽�����	
		m_bType=0;//������ģʽ��ΪFALSE
		if(AutoShowPar)                     //////
		{
			dlg.DoModal();
			int t=dlg.m_nDis;       //ƽ���߼��
			DrawPar(&dc,m_PointList,m_nPushNum,t);
		}
		m_MultiOpen=FALSE;  //�رն�����ģʽ
		ArcFlag=0;         //��Բ����ʽ��ʼ��
		TPFlag=FALSE;   //ת���ǹر�
		m_nPushNum=0;//������������Ϊ0
		delete []Arc.PointList;
		Arc.PointList=NULL;
		delete []m_PointList;
		m_PointList=NULL;
		OnDraw(&dc);   //ˢ��ҳ��

		

		
	}
//	ReleaseCapture();//�ͷŲ�׽���
	CView::OnRButtonDown(nFlags, point);    //ϵͳĬ�����
}

void CLineView::OnMultiline()                  //����������ģʽ
{
	// TODO: Add your command handler code here
	m_bType=3;
	m_MultiOpen=TRUE;
	m_PointList=new CPoint[1000];//��������ռ�
}

void CLineView::OnMultistart()                  //��������������ģʽ
{
	// TODO: Add your command handler code here
	MultiStartFlag=TRUE;
	if(MultiNum==0)
	{
		AfxMessageBox("��ǰû�л������ߣ�������Ч");
		return;
	}
	dlg5.DoModal();
}

void CLineView::OnNear()                     //���������������ģʽ
{
	// TODO: Add your command handler code here
	MultiNearFlag=TRUE;
	if(MultiNum==0)
	{
		AfxMessageBox("��ǰû�л������ߣ�������Ч");
		return;
	}
	dlg6.DoModal();

}
