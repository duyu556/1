#include "stdafx.h"
#include "FileOperation.h"

CString CFileOperation::s_horizonSectionContent = _T("");
CString CFileOperation::s_verticalSectionContent = _T("");
CFileOperation::CFileOperation()
{
	m_h0 = 0;
}


CFileOperation::~CFileOperation()
{
}

bool CFileOperation::ReadData()
{
	CFileDialog dlg(true, _T("txt"), 0, 6UL, _T("文本文件(*.txt)|*.txt||"));
	if (IDCANCEL == dlg.DoModal())
		return false;
	CString filename = dlg.GetPathName();
	CStdioFile file;
	if (!file.Open(filename, CFile::modeRead))
		return false;

	CString strline, strbuf;
	std::vector<CString> data;
	m_pOriPoint.clear();
	m_pKnowPoint.clear();

	file.ReadString(strline);
	data.clear();
	strline.Remove(' ');
	while (strline.GetLength())
	{
		strbuf = strline.SpanExcluding(_T(","));
		data.push_back(strbuf);
		strline.Delete(0, strbuf.GetLength() + 1);
	}
	if (data.size() == 2)
	{
		m_h0 = _tstof(data[1]);
	}
	else
	{
		AfxMessageBox(_T("文件打开错误！"));
		return false;
	}

	CString str1, str2, str3;
	file.ReadString(strline);
	data.clear();
	strline.Remove(' ');
	while (strline.GetLength())
	{
		strbuf = strline.SpanExcluding(_T(","));
		data.push_back(strbuf);
		strline.Delete(0, strbuf.GetLength() + 1);
	}
	if (data.size() == 3)
	{
		str1 = data[0];
		str2 = data[1];
		str3 = data[2];
	}
	else
	{
		AfxMessageBox(_T("文件打开错误！"));
		return false;
	}

	while (file.ReadString(strline))
	{
		data.clear();
		strline.Remove(' ');
		if (strline.GetLength() > 0)
		{
			while (strline.GetLength())
			{
				strbuf = strline.SpanExcluding(_T(","));
				data.push_back(strbuf);
				strline.Delete(0, strbuf.GetLength() + 1);
			}
			if (data.size() == 4)
			{
				if (data[0] == str1 || data[0] == str2 || data[0] == str3)
				{
					m_pKnowPoint.push_back(CPointInfo(data[0], _tstof(data[1]), _tstof(data[2]), _tstof(data[3])));
				}
				m_pOriPoint.push_back(CPointInfo(data[0], _tstof(data[1]), _tstof(data[2]), _tstof(data[3])));
			}
			else
			{
				AfxMessageBox(_T("文件打开错误！"));
				return false;
			}
		}
	}
	file.Close();
	return true;
}

void CFileOperation::WriteTXT()
{
	CFileDialog dlg(false, _T("txt"), 0, 6UL, _T("文本文件(*.txt)|*.txt||"));
	if (IDCANCEL == dlg.DoModal())
		return;
	CString filename = dlg.GetPathName();

	CStdioFile file;
	if (!file.Open(filename, CFile::modeCreate | CFile::modeWrite))
		return;

	CString strbuf;
	CString data = s_verticalSectionContent;
	while (data.GetLength())
	{
		strbuf = data.SpanExcluding(_T("\r\n"));
		file.WriteString(strbuf + _T("\n"));
		data.Delete(0, strbuf.GetLength() + 2);
	}
	data = s_horizonSectionContent;
	while (data.GetLength())
	{
		strbuf = data.SpanExcluding(_T("\r\n"));
		file.WriteString(strbuf + _T("\n"));
		data.Delete(0, strbuf.GetLength() + 2);
	}
	file.Close();
}

std::vector<CPointInfo> CFileOperation::OriPoint() const
{
	return m_pOriPoint;
}

std::vector<CPointInfo> CFileOperation::KnowPoint() const
{
	return m_pKnowPoint;
}

double CFileOperation::H0() const
{
	return m_h0;
}
