/******************************************************************************

版权所有 (C), 2018-2020,

******************************************************************************
文 件 名   : HorizonSectionCalc.h
版 本 号   : 初稿
作    者   :
生成日期   : 2018年10月26日
最近修改   :
功能描述   : 横断面的计算。MK0、 K1的中心点，N是K1、K2的中心点，分别过M和N点绘制横断面。
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
class CHorizonSectionCalc
{
public:
	CHorizonSectionCalc();
	~CHorizonSectionCalc();

public:
	void CalcHorizonSection(CFileOperation fileOper);							//计算横断面信息

private:
	void CalcInsertPointPosition();												//计算横断面插入点的信息
	void CalcHeight();															//计算高程
	void CalcArea(std::vector<CPointInfo>& insertpoint, double& totalArea);		//计算面积
	void WriteData(CString &content);

public:
	std::vector<CPointInfo> MHInsertPoint() const;
	std::vector<CPointInfo> NHInsertPoint() const;

private:
	std::vector<CPointInfo> m_pMHInsertPoint;									//横断面的插值
	std::vector<CPointInfo> m_pNHInsertPoint;									//横断面的插值
	CFileOperation m_fileOper;
	std::vector<CPointInfo> m_pOripoint;
	std::vector<CPointInfo> m_pKnowpoint;

	double detta;																//插值的间距

	//横断面的参数
	double am, an;																//方位角
	double mX, mY;
	double nX, nY;
	double m_mTotalArea, m_nTotalArea;											//横断面M , N的总面积
};

