/******************************************************************************

版权所有 (C), 2018-2020,

******************************************************************************
文 件 名   : ZoomView.h
版 本 号   : 初稿
作    者   :
生成日期   : 2018年10月26日
最近修改   :
功能描述   : 实现图像的放大、缩小等功能
函数列表   :
*
*

修改历史   :
1.日    期   : 2018年10月26日
作    者   :
修改内容   : 创建文件

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
	void  Move(double x, double y);			//点的移动
	void  SetPoint(double x, double y);		//设置点的值
	double m_x, m_y, m_h;
	CString m_name;
};

class CZoomView
{
public:
	CZoomView();
	~CZoomView();
public:
	static void SetData(std::vector<CCoorPoint> data);			//求取屏幕上点的分布数据
	static void SetScreenPoint(double height, double width);	//设置屏幕数据
	static void WheelScale(int zDelta);							//设置缩放比例
	static void CoorMove(int x, int y, int nflags);				//点位的移动
	static double SetX(double x);								//设置点在当前情况下的X坐标
	static double SetY(double y);								//设置点在当前情况下的Y坐标

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

