/******************************************************************************

��Ȩ���� (C), 2018-2020,

******************************************************************************
�� �� ��   : BasicCalc.h
�� �� ��   : ����
��    ��   :
��������   : 2018��10��26��
����޸�   :
��������   : �����ĺ�������
�����б�   :
*
*

�޸���ʷ   :
1.��    ��   : 2018��10��26��
��    ��   :
�޸�����   : �����ļ�

******************************************************************************/
#pragma once
#include "PointInfo.h"
#include <vector>

const double PI = 3.1415926535897932;
const double EPCLONG = 1.0e-10;
class CBasicCalc
{
public:
	CBasicCalc();
	~CBasicCalc();

	double Azimuth(double x1, double y1, double x2, double y2);
	double Distance(double x1, double y1, double x2, double y2);
	void SortDis(std::vector<CPointInfo> &p);													//ð�����򣬰������С����
	void CalcHeight(std::vector<CPointInfo>& oripoint, std::vector<CPointInfo>& insertpoint);	//����߳�
};

