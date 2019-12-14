/******************************************************************************

版权所有 (C), 2018-2020,

******************************************************************************
文 件 名   : DxfFile.h
版 本 号   : 初稿
作    者   :
生成日期   : 2018年10月26日
最近修改   :
功能描述   : 写DXF文件
函数列表   :
*
*

修改历史   :
1.日    期   : 2018年10月26日
作    者   :
修改内容   : 创建文件

******************************************************************************/
#pragma once
class CDxfFile
{
public:
	CDxfFile();
	~CDxfFile();

	bool Begin();												//dxf文件头
	void Line(double x1, double y1, double x2, double y2);		//画线
	void Point(double x1, double y1);							//画点
	void Text(double x1, double y1, CString strID);				//写文字
	void End();													//dxf文件尾

private:
	CString str;
	CStdioFile file;
};

