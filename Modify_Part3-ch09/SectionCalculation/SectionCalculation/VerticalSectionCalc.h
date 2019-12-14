/******************************************************************************

��Ȩ���� (C), 2018-2020,

******************************************************************************
�� �� ��   : VerticalSectionCalc.h
�� �� ��   : ����
��    ��   :
��������   : 2018��10��26��
����޸�   :
��������   : �ݶ���ļ��㡣K0�� K1��K2�ǵ�·�������ϵ�3���ؼ��㣬����3���㹹���ݶ��档
�����б�   :
*
*

�޸���ʷ   :
1.��    ��   : 2018��10��26��
��    ��   :
�޸�����   : �����ļ�

******************************************************************************/
#pragma once
#include "FileOperation.h"

class CVerticalSectionCalc
{
public:
	CVerticalSectionCalc();
	~CVerticalSectionCalc();

	void CalcVerticalSection(CFileOperation fileOper);	//�����ݶ�����Ϣ
private:
	void CalcInsertPointPosition();						//�����ݶ����������Ϣ
	void CalcHeight();									//����߳�
	void CalcArea();									//�������
	void WriteData(CString &content);

public:
	std::vector<CPointInfo> VInsertPoint() const;

private:
	std::vector<CPointInfo> m_pVInsertPoint;			//�ݶ���Ĳ�ֵ��
	CFileOperation m_fileOper;
	std::vector<CPointInfo> m_pOripoint;
	std::vector<CPointInfo> m_pKnowpoint;

private:
	double detta;										//��ֵ�ļ��
	double a1, a2;										//��λ��
	double m_vTotalLength;								//�ݶ����ȫ��
	double m_vTotalLength1;								//�ݶ���ĵ�һ�εĳ���
	int m_vCount1;										//�ݶ����һ�β�ֵ��ĸ���
	int m_vCount;										//�ݶ����ֵ��ĸ������ټ���.3����֪����ܸ���
	double m_vTotalArea;								//�ݶ���������
};

