/******************************************************************************

版权所有 (C), 2018-2020,

******************************************************************************
文 件 名   : FileOperation.h
版 本 号   : 初稿
作    者   :
生成日期   : 2018年10月26日
最近修改   :
功能描述   : 文件的相关操作：读取，写入。
函数列表   :
*
*

修改历史   :
1.日    期   : 2018年10月26日
作    者   :
修改内容   : 创建文件

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
	bool ReadData();								//文件读取函数
	void WriteTXT();								//输出TXT文件
public:
	std::vector<CPointInfo> OriPoint() const;
	std::vector<CPointInfo> KnowPoint() const;
	double H0() const;

public:
	CBasicCalc m_basicCalc;
	static CString s_horizonSectionContent;			//用于存储输出的rr字符串
	static CString s_verticalSectionContent;		//用于存储输出的rr字符串
private:
	std::vector<CPointInfo> m_pOriPoint;			//原始数据
	std::vector<CPointInfo> m_pKnowPoint;			//已知数据
	double m_h0;
};

