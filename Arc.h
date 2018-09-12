// Arc.h: interface for the CArc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARC_H__AE9AB635_764A_4495_9FEE_D74BD2EC696A__INCLUDED_)
#define AFX_ARC_H__AE9AB635_764A_4495_9FEE_D74BD2EC696A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include<math.h>

class CArc : public CObject  
{
public:
	int Clockwise(CPoint sp,CPoint mp,CPoint ep);
	void GetCircleAngle(CPoint sp,CPoint mp,CPoint ep,double &cangle);
	void GetVectorAngle(CPoint v1,CPoint v2,double &ang);
	CPoint m_Temp;
	void MidPoint(CPoint sp,CPoint ep,CPoint &mp);
	void ArcCalc(CPoint Start,CPoint Finish);
	void GetLineAng_Cp(CPoint sp,CPoint ep,double a,double r,CPoint &po);
	void GetLineAng_R(CPoint sp,CPoint ep,double a,double&r);
	void Polar(CPoint sp,CPoint &ep,double a,double dis);
	double GetBrAngle(CPoint sp,CPoint ep);
	double GetAzAngle(CPoint sp,CPoint ep);
	CPoint m_Center,m_Start,m_Finish,m_Turn,*PointList;
	double Radius,RM_Angle,DM_Angle,AzAngle;  //半径，弧度制角度，角度制角度，方位角
	int part;
	CArc();
	virtual ~CArc();

};

#endif // !defined(AFX_ARC_H__AE9AB635_764A_4495_9FEE_D74BD2EC696A__INCLUDED_)
