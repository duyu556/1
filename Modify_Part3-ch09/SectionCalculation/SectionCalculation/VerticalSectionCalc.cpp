#include "stdafx.h"
#include "VerticalSectionCalc.h"


CVerticalSectionCalc::CVerticalSectionCalc()
{
	detta = 10;
	a1 = 0;
	a2 = 0;	//��λ��
	m_vTotalLength = 0;	//�ݶ����ȫ��
	m_vTotalLength1 = 0;	//�ݶ���ĵ�һ�εĳ���
	m_vCount1 = 0;	//�ݶ����һ�β�ֵ��ĸ���
	m_vCount = 0;	//�ݶ����ֵ��ĸ������ټ���.3����֪����ܸ���
	m_vTotalArea = 0;	//�ݶ���������
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
	m_vCount = (int)(m_vTotalLength / detta) + 3;	//	����������֪��

	CalcInsertPointPosition();
	CalcHeight();
	CalcArea();
	AfxMessageBox(_T("�ݶ��� ������ɣ���"));

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
	content += _T("�ݶ�����Ϣ\r\n");
	content += _T("------------------------------------------------------------------------------------\r\n");
	if (m_pVInsertPoint.size() > 0)
	{
		str.Format(_T("�ݶ������:%.3lf\r\n"), m_vTotalArea);
		content += str;
		str.Format(_T("�ݶ���ȫ��:%.3lf\r\n"), m_vTotalLength);
		content += str;
		content += _T("��·����\r\n");
		content += _T("����\t���K(m)  X����(m)\tY����(m)\tH����(m)\r\n");
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
