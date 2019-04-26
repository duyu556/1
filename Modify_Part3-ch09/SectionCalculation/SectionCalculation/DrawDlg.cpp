// DrawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SectionCalculation.h"
#include "DrawDlg.h"
#include "afxdialogex.h"


// CDrawDlg �Ի���

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


// CDrawDlg ��Ϣ�������


BOOL CDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	this->GetParent()->GetClientRect(&rect);
	rect.top += 2;
	rect.left += 2;
	rect.right -= 10;
	rect.bottom -= 2;
	this->MoveWindow(rect);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CZoomView::WheelScale(zDelta);
	Invalidate();
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void CDrawDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CZoomView::CoorMove(point.x, point.y, nFlags);
	if (nFlags == 1)
		Invalidate();
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDrawDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CZoomView::Draw(dc);
}
