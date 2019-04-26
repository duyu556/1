
// SectionCalculationDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "ListDlg.h"
#include "DrawDlg.h"
#include "ReportDlg.h"
#include "HorizonSectionCalc.h"
#include "VerticalSectionCalc.h"
#include "DxfFile.h"

// CSectionCalculationDlg 对话框
class CSectionCalculationDlg : public CDialogEx
{
// 构造
public:
	CSectionCalculationDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECTIONCALCULATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnOpen();
	afx_msg void OnTxt();
	afx_msg void OnDxf();
	afx_msg void OnVcalc();
	afx_msg void OnHcalc();
	afx_msg void OnList();
	afx_msg void OnDraw();
	afx_msg void OnReport();
	afx_msg void OnUpdateTxt(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDxf(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVcalc(CCmdUI *pCmdUI);
	afx_msg void OnUpdateHcalc(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDraw(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReport(CCmdUI *pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult);
	afx_msg void OnZoomIn();
	afx_msg void OnUpdateZoomIn(CCmdUI *pCmdUI);
	afx_msg void OnZoomOut();
	afx_msg void OnUpdateZoomOut(CCmdUI *pCmdUI);
	virtual BOOL ContinueModal();

private:
	void DrawDxf();
public:
	CTabCtrl m_tab;
	CToolBar m_toolbar;
	CListDlg m_listDlg;
	CDrawDlg m_drawDlg;
	CReportDlg m_reportDlg;

	CFileOperation m_fileOper;
	CHorizonSectionCalc m_calcH;
	CVerticalSectionCalc m_calcV;
	CDxfFile m_dxf;

private:
	int ia, ib, ic, idd, ie;		//开关
};
