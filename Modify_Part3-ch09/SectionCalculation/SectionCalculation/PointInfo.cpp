#include "stdafx.h"
#include "PointInfo.h"


CPointInfo::CPointInfo()
{
	m_pointName = _T("");
	m_x = 0;
	m_y = 0;
	m_h = 0;
	m_k = 0;
	m_dis = 0;
}

CPointInfo::CPointInfo(CString pointName, double x, double y, double h, double k, double dis)
{
	m_pointName = pointName;
	m_x = x;
	m_y = y;
	m_h = h;
	m_k = k;
	m_dis = dis;
}


CPointInfo::~CPointInfo()
{
}

CString CPointInfo::PointName() const
{
	return m_pointName;
}

double CPointInfo::X() const
{
	return m_x;
}

double CPointInfo::Y() const
{
	return m_y;
}

double CPointInfo::H() const
{
	return m_h;
}

double CPointInfo::K() const
{
	return m_k;
}

double CPointInfo::Dis() const
{
	return m_dis;
}

void CPointInfo::SetPointName(CString str)
{
	m_pointName = str;
}

void CPointInfo::SetH(double h)
{
	m_h = h;
}

void CPointInfo::SetDis(double dis)
{
	m_dis = dis;
}
