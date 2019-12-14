#include "stdafx.h"
#include "HorizonSectionCalc.h"


CHorizonSectionCalc::CHorizonSectionCalc()
{
	detta = 5;
	//横断面的参数
	am = 0;
	an = 0;	//方位角
	mX = 0;
	mY = 0;
	nX = 0;
	nY = 0;
	m_mTotalArea = 0;	//横断面M的总面积
	m_nTotalArea = 0;//横断面N的总面积
}


CHorizonSectionCalc::~CHorizonSectionCalc()
{
}

void CHorizonSectionCalc::CalcHorizonSection(CFileOperation fileOper)
{
	m_fileOper = fileOper;
	m_pOripoint.clear();
	m_pOripoint = m_fileOper.OriPoint();
	m_pKnowpoint.clear();
	m_pKnowpoint = m_fileOper.KnowPoint();

	double a1 = m_fileOper.m_basicCalc.Azimuth(m_pKnowpoint[0].X(), m_pKnowpoint[0].Y(), m_pKnowpoint[1].X(), m_pKnowpoint[1].Y());
	double a2 = m_fileOper.m_basicCalc.Azimuth(m_pKnowpoint[1].X(), m_pKnowpoint[1].Y(), m_pKnowpoint[2].X(), m_pKnowpoint[2].Y());
	am = a1 - PI / 2.0;
	an = a2 - PI / 2.0;
	mX = (m_pKnowpoint[0].X() + m_pKnowpoint[1].X()) / 2.0;
	mY = (m_pKnowpoint[0].Y() + m_pKnowpoint[1].Y()) / 2.0;
	nX = (m_pKnowpoint[1].X() + m_pKnowpoint[2].X()) / 2.0;
	nY = (m_pKnowpoint[1].Y() + m_pKnowpoint[2].Y()) / 2.0;

	CalcInsertPointPosition();
	CalcHeight();
	CalcArea(m_pMHInsertPoint, m_mTotalArea);
	CalcArea(m_pNHInsertPoint, m_nTotalArea);
	AfxMessageBox(_T("横断面 计算完成！！"));

	WriteData(m_fileOper.s_horizonSectionContent);
}

void CHorizonSectionCalc::CalcInsertPointPosition()
{
	m_pMHInsertPoint.clear();
	m_pNHInsertPoint.clear();

	double dX, dY, dK;
	CString str;
	for (int i = 0; i < 11; ++i)
	{
		str.Format(_T("C%d"), i - 5);
		dX = mX + (i - 5) * detta * cos(am);
		dY = mY + (i - 5) * detta * sin(am);
		dK = i * detta;
		m_pMHInsertPoint.push_back(CPointInfo(str, dX, dY, 0, dK));
	}
	str.Format(_T("M"));
	m_pMHInsertPoint[5].SetPointName(str);

	for (int i = 0; i < 11; ++i)
	{
		str.Format(_T("C%d"), i - 5);
		dX = nX + (i - 5) * detta * cos(an);
		dY = nY + (i - 5) * detta * sin(an);
		dK = i * detta;
		m_pNHInsertPoint.push_back(CPointInfo(str, dX, dY, 0, dK));
	}
	str.Format(_T("N"));
	m_pNHInsertPoint[5].SetPointName(str);
}

void CHorizonSectionCalc::CalcHeight()
{
	m_fileOper.m_basicCalc.CalcHeight(m_pOripoint, m_pMHInsertPoint);
	m_fileOper.m_basicCalc.CalcHeight(m_pOripoint, m_pNHInsertPoint);
}

void CHorizonSectionCalc::CalcArea(std::vector<CPointInfo>& insertpoint, double& totalArea)
{
	totalArea = 0;
	double H0 = m_fileOper.H0();
	for (int i = 0; i < insertpoint.size() - 1; ++i)
	{
		totalArea += (insertpoint[i].H() + insertpoint[i + 1].H() - 2.0 * H0) / 2.0 * detta;
	}
}

void CHorizonSectionCalc::WriteData(CString & content)
{
	content = _T("");
	setlocale(LC_ALL, "");
	CString str;
	content += _T("\r\n横断面 M 信息\r\n");
	content += _T("------------------------------------------------------------------------------------\r\n");
	if (m_pMHInsertPoint.size() > 0)
	{
		str.Format(_T("横断面面积:%.3lf\r\n"), m_mTotalArea);
		content += str;
		str.Format(_T("横断面全长:50\r\n"));
		content += str;
		content += _T("线路主点\r\n");
		content += _T("点名\t里程K(m)  X坐标(m)\tY坐标(m)\tH坐标(m)\r\n");
		for (int i = 0; i < m_pMHInsertPoint.size(); ++i)
		{
			str.Format(_T("%s\t%.3lf\t%.3lf\t%.3lf\t%.3lf\r\n"), m_pMHInsertPoint[i].PointName(), m_pMHInsertPoint[i].K(), m_pMHInsertPoint[i].X(), m_pMHInsertPoint[i].Y(), m_pMHInsertPoint[i].H());
			content += str;
		}
	}

	content += _T("\r\n横断面 N 信息\r\n");
	content += _T("------------------------------------------------------------------------------------\r\n");
	if (m_pNHInsertPoint.size() > 0)
	{
		str.Format(_T("横断面面积:%.3lf\r\n"), m_nTotalArea);
		content += str;
		str.Format(_T("横断面全长:50\r\n"));
		content += str;
		content += _T("线路主点\r\n");
		content += _T("点名\t里程K(m)  X坐标(m)\tY坐标(m)\tH坐标(m)\r\n");
		for (int i = 0; i < m_pNHInsertPoint.size(); ++i)
		{
			str.Format(_T("%s\t%.3lf\t%.3lf\t%.3lf\t%.3lf\r\n"), m_pNHInsertPoint[i].PointName(), m_pNHInsertPoint[i].K(), m_pNHInsertPoint[i].X(), m_pNHInsertPoint[i].Y(), m_pNHInsertPoint[i].H());
			content += str;
		}
	}	
}

std::vector<CPointInfo> CHorizonSectionCalc::MHInsertPoint() const
{
	return m_pMHInsertPoint;
}

std::vector<CPointInfo> CHorizonSectionCalc::NHInsertPoint() const
{
	return m_pNHInsertPoint;
}
