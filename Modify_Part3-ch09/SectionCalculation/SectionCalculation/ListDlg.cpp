// ListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SectionCalculation.h"
#include "ListDlg.h"
#include "afxdialogex.h"


// CListDlg 对话框

IMPLEMENT_DYNAMIC(CListDlg, CDialogEx)

CListDlg::CListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_LIST, pParent)
{

}

CListDlg::~CListDlg()
{
}

void CListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CListDlg, CDialogEx)
END_MESSAGE_MAP()


// CListDlg 消息处理程序


BOOL CListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	this->GetParent()->GetClientRect(&rect);
	rect.top += 2;
	rect.left += 2;
	rect.right -= 10;
	rect.bottom -= 2;
	m_list.MoveWindow(rect);

	m_list.ModifyStyle(0, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list.InsertColumn(0, _T("点名"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(1, _T("X坐标"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(2, _T("Y坐标"), LVCFMT_LEFT, 150);
	m_list.InsertColumn(3, _T("H坐标"), LVCFMT_LEFT, 150);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
