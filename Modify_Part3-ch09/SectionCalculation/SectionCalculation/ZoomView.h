/******************************************************************************

��Ȩ���� (C), 2018-2020,

******************************************************************************
�� �� ��   : ZoomView.h
�� �� ��   : ����
��    ��   :
��������   : 2018��10��26��
����޸�   :
��������   : ʵ��ͼ��ķŴ���С�ȹ���
�����б�   :
*
*

�޸���ʷ   :
1.��    ��   : 2018��10��26��
��    ��   :
�޸�����   : �����ļ�

******************************************************************************/
#pragma once
#include "HorizonSectionCalc.h"
#include "VerticalSectionCalc.h"
#include <vector>

class CCoorPoint
{
public:
	CCoorPoint();
	~CCoorPoint();
public:
	void  Move(double x, double y);			//����ƶ�
	void  SetPoint(double x, double y);		//���õ��ֵ
	double m_x, m_y, m_h;
	CString m_name;
};

class CZoomView
{
public:
	CZoomView();
	~CZoomView();
public:
	static void SetData(std::vector<CCoorPoint> data);			//��ȡ��Ļ�ϵ�ķֲ�����
	static void SetScreenPoint(double height, double width);	//������Ļ����
	static void WheelScale(int zDelta);							//�������ű���
	static void CoorMove(int x, int y, int nflags);				//��λ���ƶ�
	static double SetX(double x);								//���õ��ڵ�ǰ����µ�X����
	static double SetY(double y);								//���õ��ڵ�ǰ����µ�Y����

	static void Draw(CDC &dc);
	static void SetPoint(std::vector<CCoorPoint> &m_tempOriPoint, std::vector<CPointInfo> data);

private:
	static void DrawFirstChart(CDC &dc);
	static void DrawSection(CDC &dc, std::vector<CCoorPoint> pt, double delta);

public:
	static std::vector<CCoorPoint> m_tempOriPoint;
	static std::vector<CCoorPoint> m_tempKnowPoint;
	static std::vector<CCoorPoint> m_tempVInsertPoint;
	static std::vector<CCoorPoint> m_tempMInsertPoint;
	static std::vector<CCoorPoint> m_tempNInsertPoint;

	static CCoorPoint m_dataCenterPoint;
	static CCoorPoint m_screenCenterPoint;
	static CCoorPoint m_mousePosition;

	static double m_dataHeight;
	static double m_dataWidth;
	static double m_dataScale;
	static double m_scrollScale;
};

