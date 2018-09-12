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
const double  PI = 3.1415926;//圆周率
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

double CArc::GetAzAngle(CPoint sp,CPoint ep)                           //求方向角
{
	double a=(ep.x==sp.x)?(PI/2):atan(fabs(ep.y -sp.y)/fabs(ep.x -sp.x));
	if((ep.y -sp.y)>0&&(ep.x -sp.x)<0) a=PI-a;
	if((ep.y -sp.y)<0&&(ep.x -sp.x)<0) a=PI+a;
	if((ep.y -sp.y)<0&&(ep.x -sp.x)>0) a=2*PI-a;
	return a;
}


double CArc::GetBrAngle(CPoint sp,CPoint ep)                                       //方位角
{
	sp.y=-sp.y;ep.y=-ep.y;
	double a=(ep.y==sp.y)?(PI/2):atan(fabs(ep.x -sp.x)/fabs(ep.y -sp.y));
	if((ep.y -sp.y)>0&&(ep.x -sp.x)<0) a=2*PI-a;
	if((ep.y -sp.y)<0&&(ep.x -sp.x)<0) a=PI+a;
	if((ep.y -sp.y)<0&&(ep.x -sp.x)>0) a=PI-a;
	return a;
}


void CArc::Polar(CPoint sp,CPoint &ep,double a,double dis)              //由起点、方向、距离求终点坐标
{
	ep.x=sp.x+dis*cos(a);
	ep.y=sp.y+dis*sin(a);
}

void CArc::GetLineAng_R(CPoint sp,CPoint ep,double a,double&r)					//已知圆弧端点求半径
{
	double length;//r是半径，l是弦长
	length = sqrt((sp.x - ep.x)*(sp.x - ep.x) + (sp.y - ep.y)*(sp.y - ep.y));//两点距离公式
	r = fabs(length*0.5/sin(0.5*a));//弦心距的关系
}

void CArc::GetLineAng_Cp(CPoint sp,CPoint ep,double a,double r,CPoint &po)      //已知圆弧端点及半径求圆心坐标
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
	RM_Angle=PI*DM_Angle/180;//圆心角
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
		AzAngle=GetAzAngle(Start,Finish);//方向角
		GetLineAng_R(Start,Finish,RM_Angle,Radius);//求半径
		GetLineAng_Cp(Start,Finish,RM_Angle,Radius,m_Center);//求圆心
		//计算转几次
		//part=abs(int(DM_Angle/11.25));
		part=32;
		//计算转后的点
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

void CArc::MidPoint(CPoint sp,CPoint ep,CPoint &mp)                   //求直线中点
{
	mp.x=(sp.x+ep.x)*0.5;
    mp.y=(sp.y+ep.y)*0.5;
}

void CArc::GetVectorAngle(CPoint v1,CPoint v2,double &ang)      //计算两向量坐标(用于三点画弧）
{
	double length1=sqrt(v1.x*v1.x+v1.y*v1.y);
	double length2=sqrt(v2.x*v2.x+v2.y*v2.y);
	ang=acos((v1.x*v2.x+v2.y*v1.y)/(length1*length2));
}


void CArc::GetCircleAngle(CPoint sp,CPoint mp,CPoint ep,double &cangle)   //由圆上三点计算圆心角
{
	CPoint v1=mp-sp,v2=mp-ep;
	double lineangle;
    GetVectorAngle(v1,v2,lineangle);
	cangle=2*(PI-lineangle)/PI*180;
	int flag=Clockwise(sp,mp,ep);
	//if(flag<0) cangle=-cangle;//判断顺逆时针
	//if(flag>0) cangle=-cangle;//判断顺逆时针(liu)
}


int CArc::Clockwise(CPoint sp,CPoint mp,CPoint ep)   //判断顺逆时针和三点是否共线
{
	return (mp.x-sp.x)*(ep.y-mp.y)-(mp.y-sp.y)*(ep.x-mp.x);
	//return (sp.x-mp.x)*(sp.y-mp.y)-(ep.y-mp.y)*(ep.x-mp.x);(liu)
}
