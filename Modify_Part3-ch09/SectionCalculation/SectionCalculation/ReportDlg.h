#pragma once
#include "afxwin.h"


// CReportDlg �Ի���

class CReportDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReportDlg)

public:
	CReportDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReportDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_REPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit;
	virtual BOOL OnInitDialog();
};
