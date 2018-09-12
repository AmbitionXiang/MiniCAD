// Arc.cpp: implementation of the CArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "line.h"
#include "Arc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
const double  PI = 3.1415926;//Բ����
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CArc::CArc()
{
	part=0;
	PointList=NULL;
}

CArc::~CArc()
{
	if(PointList!=NULL)
	{
		delete[]PointList;
		PointList=NULL;
	}
}

double CArc::GetAzAngle(CPoint sp,CPoint ep)                           //�����
{
	double a=(ep.x==sp.x)?(PI/2):atan(fabs(ep.y -sp.y)/fabs(ep.x -sp.x));
	if((ep.y -sp.y)>0&&(ep.x -sp.x)<0) a=PI-a;
	if((ep.y -sp.y)<0&&(ep.x -sp.x)<0) a=PI+a;
	if((ep.y -sp.y)<0&&(ep.x -sp.x)>0) a=2*PI-a;
	return a;
}


double CArc::GetBrAngle(CPoint sp,CPoint ep)                                       //��λ��
{
	sp.y=-sp.y;ep.y=-ep.y;
	double a=(ep.y==sp.y)?(PI/2):atan(fabs(ep.x -sp.x)/fabs(ep.y -sp.y));
	if((ep.y -sp.y)>0&&(ep.x -sp.x)<0) a=2*PI-a;
	if((ep.y -sp.y)<0&&(ep.x -sp.x)<0) a=PI+a;
	if((ep.y -sp.y)<0&&(ep.x -sp.x)>0) a=PI-a;
	return a;
}


void CArc::Polar(CPoint sp,CPoint &ep,double a,double dis)              //����㡢���򡢾������յ�����
{
	ep.x=sp.x+dis*cos(a);
	ep.y=sp.y+dis*sin(a);
}

void CArc::GetLineAng_R(CPoint sp,CPoint ep,double a,double&r)					//��֪Բ���˵���뾶
{
	double length;//r�ǰ뾶��l���ҳ�
	length = sqrt((sp.x - ep.x)*(sp.x - ep.x) + (sp.y - ep.y)*(sp.y - ep.y));//������빫ʽ
	r = fabs(length*0.5/sin(0.5*a));//���ľ�Ĺ�ϵ
}

void CArc::GetLineAng_Cp(CPoint sp,CPoint ep,double a,double r,CPoint &po)      //��֪Բ���˵㼰�뾶��Բ������
{
	double tgalpha=GetAzAngle(sp,ep),beta;
	if(a>0)
    beta=0.5*PI-a*0.5+tgalpha;
	else
    beta=-0.5*PI+a*0.5+tgalpha;

	po.x = sp.x + r*cos(beta);
	po.y = sp.y + r*sin(beta);
}


void CArc::ArcCalc(CPoint Start,CPoint Finish)
{
	if (PointList!=NULL)
	{
		delete []PointList;
		PointList=NULL;
	}
	if(DM_Angle>0)
		while(DM_Angle>2*180) DM_Angle-=2*180;
	if(DM_Angle<0)
		while(DM_Angle<-2*180) DM_Angle+=2*180;
	RM_Angle=PI*DM_Angle/180;//Բ�Ľ�
	if(Start==Finish)
	{
		AzAngle=0;
		Radius=0;
		m_Center=Start;
		part=0;
		PointList=NULL;
		return;
	}
	else
	{
		AzAngle=GetAzAngle(Start,Finish);//�����
		GetLineAng_R(Start,Finish,RM_Angle,Radius);//��뾶
		GetLineAng_Cp(Start,Finish,RM_Angle,Radius,m_Center);//��Բ��
		//����ת����
		//part=abs(int(DM_Angle/11.25));
		part=32;
		//����ת��ĵ�
		PointList=new CPoint[part+1];
		PointList[0]=Start;
		PointList[part]=Finish;
		double beta=GetAzAngle(m_Center,Start);
		for (int i = 1; i < part; i++)
		{
			CPoint tmp;
			//if(RM_Angle>0) beta+=PI/16;
			if(RM_Angle>0) beta+=RM_Angle/32;
			else beta-=RM_Angle/32;
			tmp.x = m_Center.x+Radius*cos(beta);
			tmp.y = m_Center.y+Radius*sin(beta);
			

			/*tmp.x = r*cos(ang1 + i*(PI/16));
			tmp.y = r*sin(ang1 + i*(PI/16));
			if(angle>0)
			tmp=-tmp+cp;
			else
			{
				tmp.x=tmp.x+cp.x;
				tmp.y=-tmp.y+cp.y;
			}*/
			PointList[i]=tmp;
		}
	}
}

void CArc::MidPoint(CPoint sp,CPoint ep,CPoint &mp)                   //��ֱ���е�
{
	mp.x=(sp.x+ep.x)*0.5;
    mp.y=(sp.y+ep.y)*0.5;
}

void CArc::GetVectorAngle(CPoint v1,CPoint v2,double &ang)      //��������������(�������㻭����
{
	double length1=sqrt(v1.x*v1.x+v1.y*v1.y);
	double length2=sqrt(v2.x*v2.x+v2.y*v2.y);
	ang=acos((v1.x*v2.x+v2.y*v1.y)/(length1*length2));
}


void CArc::GetCircleAngle(CPoint sp,CPoint mp,CPoint ep,double &cangle)   //��Բ���������Բ�Ľ�
{
	CPoint v1=mp-sp,v2=mp-ep;
	double lineangle;
    GetVectorAngle(v1,v2,lineangle);
	cangle=2*(PI-lineangle)/PI*180;
	int flag=Clockwise(sp,mp,ep);
	//if(flag<0) cangle=-cangle;//�ж�˳��ʱ��
	//if(flag>0) cangle=-cangle;//�ж�˳��ʱ��(liu)
}


int CArc::Clockwise(CPoint sp,CPoint mp,CPoint ep)   //�ж�˳��ʱ��������Ƿ���
{
	return (mp.x-sp.x)*(ep.y-mp.y)-(mp.y-sp.y)*(ep.x-mp.x);
	//return (sp.x-mp.x)*(sp.y-mp.y)-(ep.y-mp.y)*(ep.x-mp.x);(liu)
}
