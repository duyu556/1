/******************************************************************************

��Ȩ���� (C), 2018-2020,

******************************************************************************
�� �� ��   : HorizonSectionCalc.h
�� �� ��   : ����
��    ��   :
��������   : 2018��10��26��
����޸�   :
��������   : �����ļ��㡣MK0�� K1�����ĵ㣬N��K1��K2�����ĵ㣬�ֱ��M��N����ƺ���档
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
class CHorizonSectionCalc
{
public:
	CHorizonSectionCalc();
	~CHorizonSectionCalc();

public:
	void CalcHorizonSection(CFileOperation fileOper);							//����������Ϣ

private:
	void CalcInsertPointPosition();												//���������������Ϣ
	void CalcHeight();															//����߳�
	void CalcArea(std::vector<CPointInfo>& insertpoint, double& totalArea);		//�������
	void WriteData(CString &content);

public:
	std::vector<CPointInfo> MHInsertPoint() const;
	std::vector<CPointInfo> NHInsertPoint() const;

private:
	std::vector<CPointInfo> m_pMHInsertPoint;									//�����Ĳ�ֵ
	std::vector<CPointInfo> m_pNHInsertPoint;									//�����Ĳ�ֵ
	CFileOperation m_fileOper;
	std::vector<CPointInfo> m_pOripoint;
	std::vector<CPointInfo> m_pKnowpoint;

	double detta;																//��ֵ�ļ��

	//�����Ĳ���
	double am, an;																//��λ��
	double mX, mY;
	double nX, nY;
	double m_mTotalArea, m_nTotalArea;											//�����M , N�������
};

