/******************************************************************************

��Ȩ���� (C), 2018-2020,

******************************************************************************
�� �� ��   : FileOperation.h
�� �� ��   : ����
��    ��   :
��������   : 2018��10��26��
����޸�   :
��������   : �ļ�����ز�������ȡ��д�롣
�����б�   :
*
*

�޸���ʷ   :
1.��    ��   : 2018��10��26��
��    ��   :
�޸�����   : �����ļ�

******************************************************************************/
#pragma once
#include "BasicCalc.h"
#include <locale.h>

class CFileOperation
{
public:
	CFileOperation();
	~CFileOperation();
public:
	bool ReadData();								//�ļ���ȡ����
	void WriteTXT();								//���TXT�ļ�
public:
	std::vector<CPointInfo> OriPoint() const;
	std::vector<CPointInfo> KnowPoint() const;
	double H0() const;

public:
	CBasicCalc m_basicCalc;
	static CString s_horizonSectionContent;			//���ڴ洢�����rr�ַ���
	static CString s_verticalSectionContent;		//���ڴ洢�����rr�ַ���
private:
	std::vector<CPointInfo> m_pOriPoint;			//ԭʼ����
	std::vector<CPointInfo> m_pKnowPoint;			//��֪����
	double m_h0;
};

