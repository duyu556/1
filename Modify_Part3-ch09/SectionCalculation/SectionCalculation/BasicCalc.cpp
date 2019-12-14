#include "stdafx.h"
#include "BasicCalc.h"


CBasicCalc::CBasicCalc()
{
}


CBasicCalc::~CBasicCalc()
{
}

double CBasicCalc::Azimuth(double x1, double y1, double x2, double y2)//rad
{
	double a = 0;
	double x = x2 - x1;
	double y = y2 - y1;
	if (fabs(x) < EPCLONG)
	{
		if (y > 0)
			a = PI * 0.5;
		if (y < 0)
			a = PI * 1.5;
	}
	a = atan(y / x);
	if (x < 0)
		a += PI;
	if (a > 2.0 * PI)
		a -= 2.0 * PI;
	if (a < 0)
		a += 2.0 * PI;
	return a;
}

double CBasicCalc::Distance(double x1, double y1, double x2, double y2)
{
	double x = x2 - x1;
	double y = y2 - y1;
	double dis = sqrt(x * x + y * y);
	return dis;
}

void CBasicCalc::SortDis(std::vector<CPointInfo>& p)
{
	CPointInfo temp;
	for (int i = 0; i < p.size() - 1; ++i)
	{
		for (int j = 0; j < p.size() - 1 - i; ++j)
		{
			if (p[j].Dis() > p[j + 1].Dis())
			{
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
}

void CBasicCalc::CalcHeight(std::vector<CPointInfo>& oripoint, std::vector<CPointInfo>& insertpoint)
{
	double addNumerator = 0, addDenominator = 0, dis = 0;
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < oripoint.size(); ++j)
		{
			dis = Distance(oripoint[j].X(), oripoint[j].Y(), insertpoint[i].X(), insertpoint[i].Y());
			oripoint[j].SetDis(dis);
		}
		SortDis(oripoint);
		for (int k = 0; k < 20; ++k)
		{
			addNumerator += oripoint[k].H() / oripoint[k].Dis();
			addDenominator += 1.0 / oripoint[k].Dis();
		}
		insertpoint[i].SetH(addNumerator / addDenominator);
		addNumerator = 0;
		addDenominator = 0;
	}
}
