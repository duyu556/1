#include "stdafx.h"
#include "DxfFile.h"


CDxfFile::CDxfFile()
{
}


CDxfFile::~CDxfFile()
{
}

bool CDxfFile::Begin()
{
	CFileDialog dlg(false, _T("dxf"), _T("resultDXF"), 6UL, _T("DXF文件(*.dxf)|*.dxf||"));
	if (IDCANCEL == dlg.DoModal())
		return false;

	CString filename = dlg.GetPathName();
	if (!file.Open(filename, CFile::modeCreate | CFile::modeWrite))
		return false;

	file.WriteString(_T("0\n"));
	file.WriteString(_T("SECTION\n"));
	file.WriteString(_T("2\n"));
	file.WriteString(_T("ENTITIES\n"));
	return true;
}

void CDxfFile::Line(double x1, double y1, double x2, double y2)
{
	file.WriteString(_T("0\n"));
	file.WriteString(_T("LINE\n"));
	file.WriteString(_T("8\n"));
	file.WriteString(_T("0\n"));
	file.WriteString(_T("10\n"));
	str.Format(_T("%lf\n"), x1);
	file.WriteString(str);
	file.WriteString(_T("20\n"));
	str.Format(_T("%lf\n"), y1);
	file.WriteString(str);
	file.WriteString(_T("30\n"));
	file.WriteString(_T("0.0\n"));

	file.WriteString(_T("11\n"));
	str.Format(_T("%lf\n"), x2);
	file.WriteString(str);
	file.WriteString(_T("21\n"));
	str.Format(_T("%lf\n"), y2);
	file.WriteString(str);
	file.WriteString(_T("31\n"));
	file.WriteString(_T("0.0\n"));
}

void CDxfFile::Point(double x1, double y1)
{
	file.WriteString(_T("0\n"));
	file.WriteString(_T("POINT\n"));
	file.WriteString(_T("8\n"));
	file.WriteString(_T("0\n"));
	file.WriteString(_T("10\n"));
	str.Format(_T("%lf\n"), x1);
	file.WriteString(str);
	file.WriteString(_T("20\n"));
	str.Format(_T("%lf\n"), y1);
	file.WriteString(str);
	file.WriteString(_T("30\n"));
	file.WriteString(_T("0.0\n"));
}

void CDxfFile::Text(double x1, double y1, CString strID)
{
	file.WriteString(_T("0\n"));
	file.WriteString(_T("TEXT\n"));
	file.WriteString(_T("8\n"));
	file.WriteString(_T("0\n"));
	file.WriteString(_T("10\n"));
	str.Format(_T("%lf\n"), x1);
	file.WriteString(str);
	file.WriteString(_T("20\n"));
	str.Format(_T("%lf\n"), y1);
	file.WriteString(str);
	file.WriteString(_T("30\n"));
	file.WriteString(_T("0.0\n"));
	file.WriteString(_T("40\n"));
	file.WriteString(_T("10\n"));

	file.WriteString(_T("1\n"));
	str.Format(_T("%s\n"), strID);
	file.WriteString(str);
}

void CDxfFile::End()
{
	file.WriteString(_T("0\n"));
	file.WriteString(_T("ENDSEC\n"));
	file.WriteString(_T("0\n"));
	file.WriteString(_T("EOF\n"));

	file.Close();
	AfxMessageBox(_T("dxf生成完毕！！"));
}

