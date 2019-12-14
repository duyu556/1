#include "stdafx.h"
#include "ZoomView.h"

std::vector<CCoorPoint> CZoomView::m_tempOriPoint; 
std::vector<CCoorPoint> CZoomView::m_tempKnowPoint;
std::vector<CCoorPoint> CZoomView::m_tempVInsertPoint;
std::vector<CCoorPoint> CZoomView::m_tempMInsertPoint;
std::vector<CCoorPoint> CZoomView::m_tempNInsertPoint;

CCoorPoint CZoomView::m_dataCenterPoint;
CCoorPoint CZoomView::m_screenCenterPoint;
CCoorPoint CZoomView::m_mousePosition;
double CZoomView::m_dataHeight = 1;
double CZoomView::m_dataWidth = 1;
double CZoomView::m_dataScale = 1;
double CZoomView::m_scrollScale = 1;

CCoorPoint::CCoorPoint()
{
	m_x = 0;
	m_y = 0;
	m_h = 0;
	m_name = _T("");
}

CCoorPoint::~CCoorPoint()
{
}

void CCoorPoint::Move(double x, double y)
{
	m_x += x;
	m_y += y;
}

void CCoorPoint::SetPoint(double x, double y)
{
	m_x = x;
	m_y = y;
}


CZoomView::CZoomView()
{
}


CZoomView::~CZoomView()
{
}

void CZoomView::SetData(std::vector<CCoorPoint> data)
{
	double minX, minY, maxX, maxY;
	minX = data[0].m_x;
	minY = data[0].m_y;
	maxX = data[0].m_x;
	maxY = data[0].m_y;

	for (int i = 0; i < data.size(); ++i)
	{
		if (minX > data[i].m_x)
			minX = data[i].m_x;
		if (minY > data[i].m_y)
			minY = data[i].m_y;
		if (maxX < data[i].m_x)
			maxX = data[i].m_x;
		if (maxY < data[i].m_y)
			maxY = data[i].m_y;
	}
	m_dataWidth = maxX - minX;
	m_dataHeight = maxY - minY;
	m_dataCenterPoint.SetPoint((minX + maxX) / 2.0, (minY + maxY) / 2.0);
}

void CZoomView::SetScreenPoint(double height, double width)
{
	m_screenCenterPoint.SetPoint(height / 2.0, width / 2.0);
	double x_scale, y_scale;
	x_scale = m_dataWidth / width;
	y_scale = m_dataHeight / height;
	if (x_scale > y_scale)
		m_dataScale = x_scale;
	else
		m_dataScale = y_scale;
	m_dataScale *= 100;
}

void CZoomView::WheelScale(int zDelta)
{
	m_scrollScale *= (1.0 - 0.2 * zDelta / 120.0);
}

void CZoomView::CoorMove(int x, int y, int nflags)
{
	double deltaX, deltaY;
	if (nflags == 1)
	{
		deltaX = m_mousePosition.m_x - x;
		deltaY = y - m_mousePosition.m_y;
		m_dataCenterPoint.Move(deltaX * m_scrollScale * m_dataScale, deltaY * m_scrollScale * m_dataScale);
	}
	m_mousePosition.SetPoint(x, y);
}

double CZoomView::SetX(double x)
{
	double dx = (x - m_dataCenterPoint.m_x) / (m_scrollScale * m_dataScale) + m_screenCenterPoint.m_x;
	return dx;
}

double CZoomView::SetY(double y)
{
	double dy = (m_dataCenterPoint.m_y - y) / (m_scrollScale * m_dataScale) + m_screenCenterPoint.m_y;
	return dy;
}

void CZoomView::Draw(CDC & dc)
{
	DrawFirstChart(dc);
	DrawSection(dc, m_tempVInsertPoint, 0);
	DrawSection(dc, m_tempMInsertPoint, 50);
	DrawSection(dc, m_tempNInsertPoint, 50);
}

void CZoomView::SetPoint(std::vector<CCoorPoint>& m_tempOriPoint, std::vector<CPointInfo> data)
{
	m_tempOriPoint.clear();
	CCoorPoint temp;
	for (int i = 0; i < data.size(); ++i)
	{
		temp.m_name = data[i].PointName();
		temp.m_x = data[i].X();
		temp.m_y = data[i].Y();
		temp.m_h = data[i].H();
		m_tempOriPoint.push_back(temp);
	}
}

void CZoomView::DrawFirstChart(CDC &dc)
{
	//画坐标轴
	double x1, y1, x2, y2;
	x1 = SetX(4490);
	y1 = SetY(3350) * 0.5;
	dc.MoveTo(x1, y1);
	x2 = SetX(4580);
	y2 = SetY(3420) * 0.5;
	dc.LineTo(x1, y2);
	dc.MoveTo(x1, y1);
	dc.LineTo(x2, y1);
	//画刻度
	for (int i = 0; i < 5; ++i)
	{
		x1 = SetX(i * 20 + 4490);
		y2 = y1 + 5;
		dc.MoveTo(x1, y1);
		dc.LineTo(x1, y2);
	}
	for (int i = 0; i < 4; ++i)
	{
		x1 = SetX(4490);
		x2 = x1 - 5;
		y1 = SetY(3350 + i * 20) * 0.5;
		dc.MoveTo(x1, y1);
		dc.LineTo(x2, y1);
	}
	//展点
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	dc.SelectObject(&brush);
	for (int i = 0; i < m_tempOriPoint.size(); ++i)
	{
		x1 = SetX(m_tempOriPoint[i].m_x);
		y1 = SetY(m_tempOriPoint[i].m_y) * 0.5;
		dc.Ellipse(x1 - 3, y1 - 3, x1 + 3, y1 + 3);
	}
	for (int i = 0; i < m_tempKnowPoint.size(); ++i)
	{
		x1 = SetX(m_tempKnowPoint[i].m_x);
		y1 = SetY(m_tempKnowPoint[i].m_y) * 0.5;
		dc.Rectangle(x1 - 5, y1 - 5, x1 + 5, y1 + 5);
	}
	x1 = SetX(m_tempMInsertPoint[5].m_x);
	y1 = SetY(m_tempMInsertPoint[5].m_y) * 0.5;
	dc.Rectangle(x1 - 5, y1 - 5, x1 + 5, y1 + 5);
	x1 = SetX(m_tempNInsertPoint[5].m_x);
	y1 = SetY(m_tempNInsertPoint[5].m_y) * 0.5;
	dc.Rectangle(x1 - 5, y1 - 5, x1 + 5, y1 + 5);
	//画线
	CPen pen;
	dc.SelectObject(&pen);
	for (int i = 0; i < m_tempKnowPoint.size() - 1; ++i)
	{
		x1 = SetX(m_tempKnowPoint[i].m_x);
		y1 = SetY(m_tempKnowPoint[i].m_y) * 0.5;
		x2 = SetX(m_tempKnowPoint[i + 1].m_x);
		y2 = SetY(m_tempKnowPoint[i + 1].m_y) * 0.5;
		dc.MoveTo(x1, y1);
		dc.LineTo(x2, y2);
	}
	x1 = SetX(m_tempMInsertPoint[0].m_x);
	y1 = SetY(m_tempMInsertPoint[0].m_y) * 0.5;
	x2 = SetX(m_tempMInsertPoint[10].m_x);
	y2 = SetY(m_tempMInsertPoint[10].m_y) * 0.5;
	dc.MoveTo(x1, y1);
	dc.LineTo(x2, y2);
	x1 = SetX(m_tempNInsertPoint[0].m_x);
	y1 = SetY(m_tempNInsertPoint[0].m_y) * 0.5;
	x2 = SetX(m_tempNInsertPoint[10].m_x);
	y2 = SetY(m_tempNInsertPoint[10].m_y) * 0.5;
	dc.MoveTo(x1, y1);
	dc.LineTo(x2, y2);

	//写刻度，写点名
	CFont font;
	font.CreatePointFont(70, _T("楷体"));
	dc.SelectObject(&font);
	for (int i = 0; i < m_tempKnowPoint.size(); ++i)
	{
		x1 = SetX(m_tempKnowPoint[i].m_x);
		y1 = SetY(m_tempKnowPoint[i].m_y) * 0.5;
		dc.TextOut(x1, y1 - 15, m_tempKnowPoint[i].m_name);
	}
	x1 = SetX(m_tempMInsertPoint[5].m_x);
	y1 = SetY(m_tempMInsertPoint[5].m_y) * 0.5;
	dc.TextOut(x1, y1 - 15, m_tempMInsertPoint[5].m_name);
	x1 = SetX(m_tempNInsertPoint[5].m_x);
	y1 = SetY(m_tempNInsertPoint[5].m_y) * 0.5;
	dc.TextOut(x1, y1 - 15, m_tempNInsertPoint[5].m_name);
	CString str;
	for (int i = 0; i < 5; ++i)
	{
		x1 = SetX(i * 20 + 4490);
		y1 = SetY(3350) * 0.5;
		str.Format(_T("%d"), 4490 + i * 20);
		dc.TextOut(x1, y1 + 15, str);
	}
	for (int i = 0; i < 4; ++i)
	{
		x1 = SetX(4490);
		y1 = SetY(3350 + i * 20) * 0.5;
		str.Format(_T("%d"), 3350 + i * 20);
		dc.TextOut(x1 - 30, y1, str);
	}
	x1 = SetX(4530);
	y1 = SetY(3415) * 0.5;
	str.Format(_T("道路基本情况图"));
	dc.TextOut(x1, y1, str);

	y1 = SetY(3330) * 0.5;
	str.Format(_T("纵断面示意图"));
	dc.TextOut(x1, y1, str);

	y1 = SetY(3280) * 0.5;
	str.Format(_T("横断面示意图"));
	dc.TextOut(x1, y1, str);
}

void CZoomView::DrawSection(CDC &dc, std::vector<CCoorPoint> pt, double delta)
{
	//画坐标轴
	double x1, y1, x2, y2;
	x1 = SetX(4490);
	y1 = SetY(3300 - delta) * 0.5;
	dc.MoveTo(x1, y1);
	x2 = SetX(4580);
	y2 = SetY(3330 - delta) * 0.5;
	dc.LineTo(x1, y2);
	dc.MoveTo(x1, y1);
	dc.LineTo(x2, y1);
	//画刻度
	for (int i = 0; i < 5; ++i)
	{
		x1 = SetX(i * 20 + 4490);
		y2 = y1 + 5;
		dc.MoveTo(x1, y1);
		dc.LineTo(x1, y2);
	}
	for (int i = 0; i < 6; ++i)
	{
		x1 = SetX(4490);
		x2 = x1 - 5;
		y1 = SetY(3300 - delta + i * 6) * 0.5;
		dc.MoveTo(x1, y1);
		dc.LineTo(x2, y1);
	}
	double d;
	for (int i = 0; i < pt.size() - 1; ++i)
	{
		d = (4570.0 - 4490.0) / 10.0;
		x1 = SetX(i * d + 4490);
		y1 = SetY((pt[i].m_h - 10.0) * 3 + 3300 - delta) * 0.5;
		x2 = SetX((i + 1) * d + 4490);
		y2 = SetY((pt[i + 1].m_h - 10.0) * 3 + 3300 - delta) * 0.5;
		dc.MoveTo(x1, y1);
		dc.LineTo(x2, y2);
	}
	//写刻度
	CFont font;
	font.CreatePointFont(70, _T("楷体"));
	dc.SelectObject(&font);
	CString str;
	for (int i = 0; i < 5; ++i)
	{
		x1 = SetX(i * 20 + 4490);
		y1 = SetY(3300 - delta) * 0.5;
		str.Format(_T("%d"), i * 2);
		dc.TextOut(x1, y1 + 8, str);
	}
	for (int i = 0; i < 6; ++i)
	{
		x1 = SetX(4490);
		y1 = SetY(3300 - delta + i * 6) * 0.5;
		str.Format(_T("%d"), 10 + i * 2);
		dc.TextOut(x1 - 15, y1, str);
	}
}

