// ReportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SectionCalculation.h"
#include "ReportDlg.h"
#include "afxdialogex.h"


// CReportDlg 对话框

IMPLEMENT_DYNAMIC(CReportDlg, CDialogEx)

CReportDlg::CReportDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_REPORT, pParent)
{

}

CReportDlg::~CReportDlg()
{
}

void CReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CReportDlg, CDialogEx)
END_MESSAGE_MAP()


// CReportDlg 消息处理程序


BOOL CReportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	this->GetParent()->GetClientRect(&rect);
	rect.top += 2;
	rect.left += 2;
	rect.right -= 10;
	rect.bottom -= 2;
	m_edit.MoveWindow(rect);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
