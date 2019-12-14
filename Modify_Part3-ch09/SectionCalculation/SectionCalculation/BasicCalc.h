/******************************************************************************

版权所有 (C), 2018-2020,

******************************************************************************
文 件 名   : BasicCalc.h
版 本 号   : 初稿
作    者   :
生成日期   : 2018年10月26日
最近修改   :
功能描述   : 基本的函数计算
函数列表   :
*
*

修改历史   :
1.日    期   : 2018年10月26日
作    者   :
修改内容   : 创建文件

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
	void SortDis(std::vector<CPointInfo> &p);													//冒泡排序，按距离从小到大
	void CalcHeight(std::vector<CPointInfo>& oripoint, std::vector<CPointInfo>& insertpoint);	//计算高程
};

