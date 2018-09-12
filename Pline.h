// Pline.h: interface for the CPline class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLINE_H__3D2FB523_D781_49B3_9911_369DFBB01A00__INCLUDED_)
#define AFX_PLINE_H__3D2FB523_D781_49B3_9911_369DFBB01A00__INCLUDED_

#include "Dlg2.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CPline :public CObject
{
public:
	CPen pen[1000];
	void DrawPar(CDC *pDC,CPoint &ParFlag);
	void GetInterPoint(double A,double B,double C,double a,double b,double c,CPoint &pt);//得到交点
	void GetParam(double &A,double &B,double &C,CPoint m_ptStart,CPoint m_ptEnd) const;  //得到线段的一般式方程参数
	CPoint* GetPList(); 
	int GetNumber();
	CDlg2 Dlg2pline;
	void Draw(CDC *pDC,int n);
	CPline();
	CPline(int Number,CPoint *PointList);
	virtual ~CPline();
	
private:
	float m_LineWidth;//线宽
	short m_LineType;//线型
	COLORREF m_ColorPen;//笔色
	COLORREF m_ColorBrush;//填充颜色
	int m_Number;//连续直线和多边形区域的顶点数目
	CPoint *m_PointList;//存储点的数组指针
};

#endif // !defined(AFX_PLINE_H__3D2FB523_D781_49B3_9911_369DFBB01A00__INCLUDED_)
