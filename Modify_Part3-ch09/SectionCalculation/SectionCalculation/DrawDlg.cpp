// DrawDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SectionCalculation.h"
#include "DrawDlg.h"
#include "afxdialogex.h"


// CDrawDlg 对话框

IMPLEMENT_DYNAMIC(CDrawDlg, CDialogEx)

CDrawDlg::CDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_DRAW, pParent)
{

}

CDrawDlg::~CDrawDlg()
{
}

void CDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrawDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDrawDlg 消息处理程序


BOOL CDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	this->GetParent()->GetClientRect(&rect);
	rect.top += 2;
	rect.left += 2;
	rect.right -= 10;
	rect.bottom -= 2;
	this->MoveWindow(rect);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDrawDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (::IsWindow(m_hWnd))
	{
		CZoomView::SetScreenPoint(cx, cy);
		Invalidate();
	}
}


BOOL CDrawDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CZoomView::WheelScale(zDelta);
	Invalidate();
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CDrawDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CZoomView::CoorMove(point.x, point.y, nFlags);
	if (nFlags == 1)
		Invalidate();
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDrawDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CZoomView::Draw(dc);
}
