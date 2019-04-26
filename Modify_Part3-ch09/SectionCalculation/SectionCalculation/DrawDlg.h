#pragma once
#include "ZoomView.h"

// CDrawDlg �Ի���

class CDrawDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDrawDlg)

public:
	CDrawDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrawDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_DRAW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};
