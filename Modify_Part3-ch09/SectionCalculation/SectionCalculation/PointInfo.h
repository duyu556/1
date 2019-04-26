/******************************************************************************

��Ȩ���� (C), 2018-2020,

******************************************************************************
�� �� ��   : PointInfo.h
�� �� ��   : ����
��    ��   :
��������   : 2018��10��26��
����޸�   :
��������   : �洢��λ��Ϣ
�����б�   :
*
*

�޸���ʷ   :
1.��    ��   : 2018��10��26��
��    ��   :
�޸�����   : �����ļ�

******************************************************************************/
#pragma once
class CPointInfo
{
public:
	CPointInfo();
	CPointInfo(CString pointName, double x, double y, double h, double k = 0, double dis = 0);
	~CPointInfo();
public:
	CString PointName() const;
	double X() const;
	double Y() const;
	double H() const;
	double K() const;
	double Dis() const;
	void SetPointName(CString str);
	void SetH(double h);
	void SetDis(double dis);

private:
	CString m_pointName;			//����
	double m_x;						//x����
	double m_y;						//y����
	double m_h;						//h����
	double m_k;						//���
	double m_dis;					//����
};

