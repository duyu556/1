/******************************************************************************

版权所有 (C), 2018-2020,

******************************************************************************
文 件 名   : VerticalSectionCalc.h
版 本 号   : 初稿
作    者   :
生成日期   : 2018年10月26日
最近修改   :
功能描述   : 纵断面的计算。K0， K1，K2是道路中心线上的3个关键点，过这3个点构建纵断面。
函数列表   :
*
*

修改历史   :
1.日    期   : 2018年10月26日
作    者   :
修改内容   : 创建文件

******************************************************************************/
#pragma once
#include "FileOperation.h"

class CVerticalSectionCalc
{
public:
	CVerticalSectionCalc();
	~CVerticalSectionCalc();

	void CalcVerticalSection(CFileOperation fileOper);	//计算纵断面信息
private:
	void CalcInsertPointPosition();						//计算纵断面插入点的信息
	void CalcHeight();									//计算高程
	void CalcArea();									//计算面积
	void WriteData(CString &content);

public:
	std::vector<CPointInfo> VInsertPoint() const;

private:
	std::vector<CPointInfo> m_pVInsertPoint;			//纵断面的插值点
	CFileOperation m_fileOper;
	std::vector<CPointInfo> m_pOripoint;
	std::vector<CPointInfo> m_pKnowpoint;

private:
	double detta;										//插值的间距
	double a1, a2;										//方位角
	double m_vTotalLength;								//纵断面的全长
	double m_vTotalLength1;								//纵断面的第一段的长度
	int m_vCount1;										//纵断面第一段插值点的个数
	int m_vCount;										//纵断面插值点的个数，再加上.3个已知点的总个数
	double m_vTotalArea;								//纵断面的总面积
};

