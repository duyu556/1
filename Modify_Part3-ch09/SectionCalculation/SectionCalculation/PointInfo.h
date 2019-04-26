/******************************************************************************

版权所有 (C), 2018-2020,

******************************************************************************
文 件 名   : PointInfo.h
版 本 号   : 初稿
作    者   :
生成日期   : 2018年10月26日
最近修改   :
功能描述   : 存储点位信息
函数列表   :
*
*

修改历史   :
1.日    期   : 2018年10月26日
作    者   :
修改内容   : 创建文件

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
	CString m_pointName;			//点名
	double m_x;						//x坐标
	double m_y;						//y坐标
	double m_h;						//h坐标
	double m_k;						//里程
	double m_dis;					//距离
};

