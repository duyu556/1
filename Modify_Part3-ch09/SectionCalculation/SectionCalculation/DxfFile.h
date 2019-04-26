/******************************************************************************

��Ȩ���� (C), 2018-2020,

******************************************************************************
�� �� ��   : DxfFile.h
�� �� ��   : ����
��    ��   :
��������   : 2018��10��26��
����޸�   :
��������   : дDXF�ļ�
�����б�   :
*
*

�޸���ʷ   :
1.��    ��   : 2018��10��26��
��    ��   :
�޸�����   : �����ļ�

******************************************************************************/
#pragma once
class CDxfFile
{
public:
	CDxfFile();
	~CDxfFile();

	bool Begin();												//dxf�ļ�ͷ
	void Line(double x1, double y1, double x2, double y2);		//����
	void Point(double x1, double y1);							//����
	void Text(double x1, double y1, CString strID);				//д����
	void End();													//dxf�ļ�β

private:
	CString str;
	CStdioFile file;
};

