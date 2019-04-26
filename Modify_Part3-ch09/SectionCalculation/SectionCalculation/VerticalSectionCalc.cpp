#include "stdafx.h"
#include "VerticalSectionCalc.h"


CVerticalSectionCalc::CVerticalSectionCalc()
{
	detta = 10;
	a1 = 0;
	a2 = 0;	//方位角
	m_vTotalLength = 0;	//纵断面的全长
	m_vTotalLength1 = 0;	//纵断面的第一段的长度
	m_vCount1 = 0;	//纵断面第一段插值点的个数
	m_vCount = 0;	//纵断面插值点的个数，再加上.3个已知点的总个数
	m_vTotalArea = 0;	//纵断面的总面积
}


CVerticalSectionCalc::~CVerticalSectionCalc()
{
}

void CVerticalSectionCalc::CalcVerticalSection(CFileOperation fileOper)
{
	m_fileOper = fileOper;
	m_pOripoint.clear();
	m_pOripoint = m_fileOper.OriPoint();
	m_pKnowpoint.clear();
	m_pKnowpoint = m_fileOper.KnowPoint();

	m_pVInsertPoint.clear();

	a1 = m_fileOper.m_basicCalc.Azimuth(m_pKnowpoint[0].X(), m_pKnowpoint[0].Y(), m_pKnowpoint[1].X(), m_pKnowpoint[1].Y());
	a2 = m_fileOper.m_basicCalc.Azimuth(m_pKnowpoint[1].X(), m_pKnowpoint[1].Y(), m_pKnowpoint[2].X(), m_pKnowpoint[2].Y());
	m_vTotalLength1 = m_fileOper.m_basicCalc.Distance(m_pKnowpoint[0].X(), m_pKnowpoint[0].Y(), m_pKnowpoint[1].X(), m_pKnowpoint[1].Y());
	m_vTotalLength = m_vTotalLength1 + m_fileOper.m_basicCalc.Distance(m_pKnowpoint[1].X(), m_pKnowpoint[1].Y(), m_pKnowpoint[2].X(), m_pKnowpoint[2].Y());
	m_vCount1 = (int)(m_vTotalLength1 / detta);
	m_vCount = (int)(m_vTotalLength / detta) + 3;	//	加上三个已知点

	CalcInsertPointPosition();
	CalcHeight();
	CalcArea();
	AfxMessageBox(_T("纵断面 计算完成！！"));

	WriteData(m_fileOper.s_verticalSectionContent);
}

void CVerticalSectionCalc::CalcInsertPointPosition()
{	
	m_pVInsertPoint.push_back(CPointInfo(m_pKnowpoint[0].PointName(), m_pKnowpoint[0].X(), m_pKnowpoint[0].Y(), m_pKnowpoint[0].H()));
	double dX, dY, dK;
	CString str;
	for (int i = 0; i < m_vCount1; ++i)
	{
		str.Format(_T("V-%d"), i + 1);
		dX = m_pKnowpoint[0].X() + detta * (i + 1) * cos(a1);
		dY = m_pKnowpoint[0].Y() + detta * (i + 1) * sin(a1);
		dK = (i + 1) * detta;
		m_pVInsertPoint.push_back(CPointInfo(str, dX, dY, 0, dK));
	}
	m_pVInsertPoint.push_back(CPointInfo(m_pKnowpoint[1].PointName(), m_pKnowpoint[1].X(), m_pKnowpoint[1].Y(), m_pKnowpoint[1].H(), m_vTotalLength1));

	double dis = m_fileOper.m_basicCalc.Distance(m_pVInsertPoint[m_vCount1].X(), m_pVInsertPoint[m_vCount1].Y(), m_pKnowpoint[1].X(), m_pKnowpoint[1].Y());
	for (int i = m_vCount1; i < m_vCount - 3; ++i)
	{
		str.Format(_T("V-%d"), i + 1);
		dX = m_pKnowpoint[1].X() + (detta - dis + detta * (i - m_vCount1)) * cos(a2);
		dY = m_pKnowpoint[1].Y() + (detta - dis + detta * (i - m_vCount1)) * sin(a2);
		dK = (i + 1) * detta;
		m_pVInsertPoint.push_back(CPointInfo(str, dX, dY, 0, dK));
	}
	m_pVInsertPoint.push_back(CPointInfo(m_pKnowpoint[2].PointName(), m_pKnowpoint[2].X(), m_pKnowpoint[2].Y(), m_pKnowpoint[2].H(), m_vTotalLength));
}

void CVerticalSectionCalc::CalcHeight()
{
	m_fileOper.m_basicCalc.CalcHeight(m_pOripoint, m_pVInsertPoint);
	m_pVInsertPoint[0].SetH(m_pKnowpoint[0].H());
	m_pVInsertPoint[m_vCount1 + 1].SetH(m_pKnowpoint[1].H());
	m_pVInsertPoint[m_vCount - 1].SetH(m_pKnowpoint[2].H());
}

void CVerticalSectionCalc::CalcArea()
{
	m_vTotalArea = 0;
	double H0 = m_fileOper.H0();
	for (int i = 0; i < m_pVInsertPoint.size() - 1; ++i)
	{
		m_vTotalArea += (m_pVInsertPoint[i].H() + m_pVInsertPoint[i + 1].H() - 2.0 * H0) 
			/ 2.0 * m_fileOper.m_basicCalc.Distance(m_pVInsertPoint[i].X(), m_pVInsertPoint[i].Y(), m_pVInsertPoint[i + 1].X(), m_pVInsertPoint[i + 1].Y());
	}
}

void CVerticalSectionCalc::WriteData(CString &content)
{
	content = _T("");
	setlocale(LC_ALL, "");
	CString str;
	content += _T("纵断面信息\r\n");
	content += _T("------------------------------------------------------------------------------------\r\n");
	if (m_pVInsertPoint.size() > 0)
	{
		str.Format(_T("纵断面面积:%.3lf\r\n"), m_vTotalArea);
		content += str;
		str.Format(_T("纵断面全长:%.3lf\r\n"), m_vTotalLength);
		content += str;
		content += _T("线路主点\r\n");
		content += _T("点名\t里程K(m)  X坐标(m)\tY坐标(m)\tH坐标(m)\r\n");
		for (int i = 0; i < m_pVInsertPoint.size(); ++i)
		{
			str.Format(_T("%s\t%.3lf\t%.3lf\t%.3lf\t%.3lf\r\n"), m_pVInsertPoint[i].PointName(), m_pVInsertPoint[i].K(), m_pVInsertPoint[i].X(), m_pVInsertPoint[i].Y(), m_pVInsertPoint[i].H());
			content += str;
		}
	}	
}

std::vector<CPointInfo> CVerticalSectionCalc::VInsertPoint() const
{
	return m_pVInsertPoint;
}
