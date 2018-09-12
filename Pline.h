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
	void GetInterPoint(double A,double B,double C,double a,double b,double c,CPoint &pt);//�õ�����
	void GetParam(double &A,double &B,double &C,CPoint m_ptStart,CPoint m_ptEnd) const;  //�õ��߶ε�һ��ʽ���̲���
	CPoint* GetPList(); 
	int GetNumber();
	CDlg2 Dlg2pline;
	void Draw(CDC *pDC,int n);
	CPline();
	CPline(int Number,CPoint *PointList);
	virtual ~CPline();
	
private:
	float m_LineWidth;//�߿�
	short m_LineType;//����
	COLORREF m_ColorPen;//��ɫ
	COLORREF m_ColorBrush;//�����ɫ
	int m_Number;//����ֱ�ߺͶ��������Ķ�����Ŀ
	CPoint *m_PointList;//�洢�������ָ��
};

#endif // !defined(AFX_PLINE_H__3D2FB523_D781_49B3_9911_369DFBB01A00__INCLUDED_)
