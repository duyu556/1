// ReportDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SectionCalculation.h"
#include "ReportDlg.h"
#include "afxdialogex.h"


// CReportDlg �Ի���

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


// CReportDlg ��Ϣ�������


BOOL CReportDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	this->GetParent()->GetClientRect(&rect);
	rect.top += 2;
	rect.left += 2;
	rect.right -= 10;
	rect.bottom -= 2;
	m_edit.MoveWindow(rect);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
