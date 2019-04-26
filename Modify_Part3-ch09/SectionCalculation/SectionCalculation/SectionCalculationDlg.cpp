
// SectionCalculationDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SectionCalculation.h"
#include "SectionCalculationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSectionCalculationDlg 对话框



CSectionCalculationDlg::CSectionCalculationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SECTIONCALCULATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ia = 0;
	ib = 0;
	ic = 0;
	idd = 0;
	ie = 0;
}

void CSectionCalculationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CSectionCalculationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CSectionCalculationDlg::OnSelchangeTab1)
	ON_COMMAND(IDM_OPEN, &CSectionCalculationDlg::OnOpen)
	ON_COMMAND(IDM_TXT, &CSectionCalculationDlg::OnTxt)
	ON_COMMAND(IDM_DXF, &CSectionCalculationDlg::OnDxf)
	ON_COMMAND(IDM_VCALC, &CSectionCalculationDlg::OnVcalc)
	ON_COMMAND(IDM_HCALC, &CSectionCalculationDlg::OnHcalc)
	ON_COMMAND(IDM_LIST, &CSectionCalculationDlg::OnList)
	ON_COMMAND(IDM_DRAW, &CSectionCalculationDlg::OnDraw)
	ON_COMMAND(IDM_REPORT, &CSectionCalculationDlg::OnReport)
	ON_UPDATE_COMMAND_UI(IDM_TXT, &CSectionCalculationDlg::OnUpdateTxt)
	ON_UPDATE_COMMAND_UI(IDM_DXF, &CSectionCalculationDlg::OnUpdateDxf)
	ON_UPDATE_COMMAND_UI(IDM_VCALC, &CSectionCalculationDlg::OnUpdateVcalc)
	ON_UPDATE_COMMAND_UI(IDM_HCALC, &CSectionCalculationDlg::OnUpdateHcalc)
	ON_UPDATE_COMMAND_UI(IDM_DRAW, &CSectionCalculationDlg::OnUpdateDraw)
	ON_UPDATE_COMMAND_UI(IDM_REPORT, &CSectionCalculationDlg::OnUpdateReport)
	ON_WM_INITMENUPOPUP()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipNotify)
	ON_COMMAND(IDM_ZOOM_IN, &CSectionCalculationDlg::OnZoomIn)
	ON_UPDATE_COMMAND_UI(IDM_ZOOM_IN, &CSectionCalculationDlg::OnUpdateZoomIn)
	ON_COMMAND(IDM_ZOOM_OUT, &CSectionCalculationDlg::OnZoomOut)
	ON_UPDATE_COMMAND_UI(IDM_ZOOM_OUT, &CSectionCalculationDlg::OnUpdateZoomOut)
END_MESSAGE_MAP()


// CSectionCalculationDlg 消息处理程序

BOOL CSectionCalculationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。
	m_toolbar.CreateEx(this);
	m_toolbar.LoadToolBar(IDR_TOOLBAR1);
	CRect rect1;
	GetClientRect(&rect1);
	m_toolbar.MoveWindow(0, 0, rect1.Width(), 50);
	m_toolbar.EnableToolTips(TRUE);

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_tab.InsertItem(0, _T("表格"));
	m_tab.InsertItem(1, _T("绘图"));
	m_tab.InsertItem(2, _T("报表"));

	m_listDlg.Create(IDD_DLG_LIST, &m_tab);
	m_drawDlg.Create(IDD_DLG_DRAW, &m_tab);
	m_reportDlg.Create(IDD_DLG_REPORT, &m_tab);

	m_listDlg.ShowWindow(SW_SHOW);
	m_drawDlg.ShowWindow(SW_HIDE);
	m_reportDlg.ShowWindow(SW_HIDE);

	//获取tab控件的大小
	CRect rect;
	m_tab.GetClientRect(&rect);
	rect.top += 2;
	rect.left += 1;
	rect.right -= 2;
	rect.bottom -= 22;
	m_listDlg.MoveWindow(rect);
	m_drawDlg.MoveWindow(rect);
	m_reportDlg.MoveWindow(rect);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSectionCalculationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSectionCalculationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSectionCalculationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSectionCalculationDlg::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nSelect = m_tab.GetCurSel();
	if (nSelect == 0)
	{
		m_listDlg.ShowWindow(SW_SHOW);
		m_drawDlg.ShowWindow(SW_HIDE);
		m_reportDlg.ShowWindow(SW_HIDE);
	}
	if (nSelect == 1 && idd == 1)
	{
		m_listDlg.ShowWindow(SW_HIDE);
		m_drawDlg.ShowWindow(SW_SHOW);
		m_reportDlg.ShowWindow(SW_HIDE);
	}
	if (nSelect == 2 && ie == 1)
	{
		m_listDlg.ShowWindow(SW_HIDE);
		m_drawDlg.ShowWindow(SW_HIDE);
		m_reportDlg.ShowWindow(SW_SHOW);
	}
	*pResult = 0;
}


void CSectionCalculationDlg::OnOpen()
{
	if (false == m_fileOper.ReadData())
	{
		ia = 0;
		ib = 0;
		ic = 0;
		idd = 0;
		ie = 0;
		return;
	}
	m_listDlg.m_list.DeleteAllItems();
	CString str;
	for (int i = 0; i < m_fileOper.OriPoint().size(); ++i)
	{
		m_listDlg.m_list.InsertItem(i, _T(""));
		m_listDlg.m_list.SetItemText(i, 0, m_fileOper.OriPoint()[i].PointName());
		str.Format(_T("%lf"), m_fileOper.OriPoint()[i].X());
		m_listDlg.m_list.SetItemText(i, 1, str);

		str.Format(_T("%lf"), m_fileOper.OriPoint()[i].Y());
		m_listDlg.m_list.SetItemText(i, 2, str);

		str.Format(_T("%lf"), m_fileOper.OriPoint()[i].H());
		m_listDlg.m_list.SetItemText(i, 3, str);
	}
	ia = 1;
	ib = 0;
	ic = 0;
	idd = 0;
	m_listDlg.ShowWindow(SW_SHOW);
	m_drawDlg.ShowWindow(SW_HIDE);
	m_reportDlg.ShowWindow(SW_HIDE);
	m_tab.SetCurSel(0);
}


void CSectionCalculationDlg::OnTxt()
{
	m_fileOper.WriteTXT();
}


void CSectionCalculationDlg::OnDxf()
{
	DrawDxf();
}


void CSectionCalculationDlg::OnVcalc()
{
	m_calcV.CalcVerticalSection(m_fileOper);
	ia = 0;
	ib = 1;
	ic = 0;
	idd = 0;
	ie = 0;
}


void CSectionCalculationDlg::OnHcalc()
{
	m_calcH.CalcHorizonSection(m_fileOper);
	ia = 0;
	ib = 0;
	ic = 1;
	idd = 0;
	ie = 0;
}


void CSectionCalculationDlg::OnList()
{
	m_listDlg.ShowWindow(SW_SHOW);
	m_drawDlg.ShowWindow(SW_HIDE);
	m_reportDlg.ShowWindow(SW_HIDE);
	m_tab.SetCurSel(0);
}


void CSectionCalculationDlg::OnDraw()
{
	CZoomView::SetPoint(CZoomView::m_tempOriPoint, m_fileOper.OriPoint());
	CZoomView::SetPoint(CZoomView::m_tempKnowPoint, m_fileOper.KnowPoint());
	CZoomView::SetPoint(CZoomView::m_tempVInsertPoint, m_calcV.VInsertPoint());
	CZoomView::SetPoint(CZoomView::m_tempMInsertPoint, m_calcH.MHInsertPoint());
	CZoomView::SetPoint(CZoomView::m_tempNInsertPoint, m_calcH.NHInsertPoint());
	CZoomView::SetData(CZoomView::m_tempOriPoint);
	m_listDlg.ShowWindow(SW_HIDE);
	m_drawDlg.ShowWindow(SW_SHOW);
	m_reportDlg.ShowWindow(SW_HIDE);
	m_tab.SetCurSel(1);
	idd = 1;
}


void CSectionCalculationDlg::OnReport()
{
	CString content = m_fileOper.s_verticalSectionContent + m_fileOper.s_horizonSectionContent;
	m_reportDlg.m_edit.SetWindowTextW(content);
	m_listDlg.ShowWindow(SW_HIDE);
	m_drawDlg.ShowWindow(SW_HIDE);
	m_reportDlg.ShowWindow(SW_SHOW);
	m_tab.SetCurSel(2);
	ie = 1;
}


void CSectionCalculationDlg::OnUpdateTxt(CCmdUI *pCmdUI)
{
	if (ic == 1)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}


void CSectionCalculationDlg::OnUpdateDxf(CCmdUI *pCmdUI)
{
	if (ic == 1)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}


void CSectionCalculationDlg::OnUpdateVcalc(CCmdUI *pCmdUI)
{
	if (ia == 1)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}


void CSectionCalculationDlg::OnUpdateHcalc(CCmdUI *pCmdUI)
{
	if (ib == 1)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}


void CSectionCalculationDlg::OnUpdateDraw(CCmdUI *pCmdUI)
{
	if (ic == 1)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}


void CSectionCalculationDlg::OnUpdateReport(CCmdUI *pCmdUI)
{
	if (ic == 1)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}

void CSectionCalculationDlg::DrawDxf()
{
	if (false == m_dxf.Begin())
		return;

	//画坐标轴： 横轴都为1500， 纵轴为1500起 长度为500
	m_dxf.Line(0, 1500, 1500, 1500);//h
	m_dxf.Line(0, 1500, 0, 2000);//v
	//绘制刻度
	double dv = 500.0 / 3.0;
	double dh = 1500.0 / 4.0;
	double dX, dY;
	CString str;
	for (int i = 0; i < 4; ++i)
	{
		dX = dh * i;
		dY = dv * i + 1500;
		m_dxf.Line(0, dY, -10, dY);//v
		m_dxf.Line(dX, 1500, dX, 1490);//h
		str.Format(_T("%d"), 3350 + 20 * i);
		m_dxf.Text(-80, dY, str);
		str.Format(_T("%d"), 4490 + 20 * i);
		m_dxf.Text(dX, 1470, str);
	}
	str.Format(_T("%d"), 4570);
	m_dxf.Text(1500, 1470, str);

	//画第二个坐标轴  700z -- 1200
	m_dxf.Line(0, 700, 1500, 700);	//h
	m_dxf.Line(0, 700, 0, 1200);	//z
	dv = 500.0 / 5.0;
	dh = 1500.0 / 5.0;
	for (int i = 0; i < 6; ++i)
	{
		dY = dv * i + 700;
		dX = dh * i;
		m_dxf.Line(0, dY, -10, dY);	//v
		m_dxf.Line(dX, 700, dX, 690);	//h
		str.Format(_T("%d"), 10 + 2 * i);
		m_dxf.Text(-80, dY, str);
		str.Format(_T("%d"), 2 * i);
		m_dxf.Text(dX, 670, str);
	}

	//画第三个坐标轴  0-500
	m_dxf.Line(0, 0, 1500, 0);	//h
	m_dxf.Line(0, 0, 0, 500);	//z
	dv = 500.0 / 5.0;
	dh = 1500.0 / 5.0;
	for (int i = 0; i < 6; ++i)
	{
		dY = dv * i;
		dX = dh * i;
		m_dxf.Line(0, dY, -10, dY);	//z
		m_dxf.Line(dX, 0, dX, -10);	//h
		str.Format(_T("%d"), 10 + 2 * i);
		m_dxf.Text(-80, dY, str);
		str.Format(_T("%d"), 2 * i);
		m_dxf.Text(dX, -30, str);
	}

	//在第一个坐标系上展点
	for (int i = 0; i < m_fileOper.OriPoint().size(); ++i)
	{
		dX = (m_fileOper.OriPoint()[i].X() - 4490) * 1500 / (4570 - 4490);
		dY = 1500 + (m_fileOper.OriPoint()[i].Y() - 3350) * 500 / (3410 - 3350);
		m_dxf.Point(dX, dY);
	}
	for (int i = 0; i < 3; ++i)
	{
		dX = (m_fileOper.KnowPoint()[i].X() - 4490) * 1500 / (4570 - 4490);
		dY = 1500 + (m_fileOper.KnowPoint()[i].Y() - 3350) * 500 / (3410 - 3350);
		m_dxf.Point(dX, dY);
		dY += 20;
		m_dxf.Text(dX, dY, m_fileOper.KnowPoint()[i].PointName());
	}
	dX = (m_fileOper.KnowPoint()[2].X() - 4490) * 1500 / (4570 - 4490);
	dY = 1500 + (m_fileOper.KnowPoint()[2].Y() - 3350) * 500 / (3410 - 3350);
	double dX1, dY1;
	dX1 = (m_fileOper.KnowPoint()[0].X() - 4490) * 1500 / (4570 - 4490);
	dY1 = 1500 + (m_fileOper.KnowPoint()[0].Y() - 3350) * 500 / (3410 - 3350);
	m_dxf.Line(dX, dY, dX1, dY1);

	//绘制M点
	dX = (m_calcH.MHInsertPoint()[5].X() - 4490) * 1500 / (4570 - 4490);
	dY = 1500 + (m_calcH.MHInsertPoint()[5].Y() - 3350) * 500 / (3410 - 3350) + 20;
	m_dxf.Text(dX, dY, m_calcH.MHInsertPoint()[5].PointName());

	//绘制N点
	dX = (m_calcH.NHInsertPoint()[5].X() - 4490) * 1500.0 / (4570 - 4490);
	dY = 1500 + (m_calcH.NHInsertPoint()[5].Y() - 3350) * 500.0 / (3410 - 3350) + 20;
	m_dxf.Text(dX, dY, m_calcH.NHInsertPoint()[5].PointName());

	//画出M线
	dX = (m_calcH.MHInsertPoint()[10].X() - 4490) * 1500.0 / (4570 - 4490);
	dY = 1500 + (m_calcH.MHInsertPoint()[10].Y() - 3350) * 500.0 / (3410 - 3350);
	dX1 = (m_calcH.MHInsertPoint()[0].X() - 4490) * 1500.0 / (4570 - 4490);
	dY1 = 1500 + (m_calcH.MHInsertPoint()[0].Y() - 3350) * 500.0 / (3410 - 3350);
	m_dxf.Line(dX, dY, dX1, dY1);

	//画出N线
	dX = (m_calcH.NHInsertPoint()[10].X() - 4490) * 1500.0 / (4570 - 4490);
	dY = 1500 + (m_calcH.NHInsertPoint()[10].Y() - 3350) * 500.0 / (3410 - 3350);
	dX1 = (m_calcH.NHInsertPoint()[0].X() - 4490) * 1500.0 / (4570 - 4490);
	dY1 = 1500 + (m_calcH.NHInsertPoint()[0].Y() - 3350) * 500.0 / (3410 - 3350);
	m_dxf.Line(dX, dY, dX1, dY1);

	//画纵断面
	for (int i = 0; i < m_calcV.VInsertPoint().size() - 1; ++i)
	{
		dX = i * 1500.0 / 10.0;
		dY = 700 + (m_calcV.VInsertPoint()[i].H() - 10) * 500.0 / 10.0;
		dX1 = (i + 1) * 1500 / 10.0;
		dY1 = 700 + (m_calcV.VInsertPoint()[i + 1].H() - 10) * 500.0 / 10.0;
		m_dxf.Point(dX, dY);
		m_dxf.Line(dX, dY, dX1, dY1);
	}

	//画M横断面线
	for (int i = 0; i < 10; ++i)
	{
		dX = i * 1500.0 / 10.0;
		dY = (m_calcH.MHInsertPoint()[i].H() - 10) * 500.0 / 10.0;
		dX1 = (i + 1) * 1500.0 / 10.0;
		dY1 = (m_calcH.MHInsertPoint()[i + 1].H() - 10) * 500.0 / 10.0;
		m_dxf.Point(dX, dY);
		m_dxf.Line(dX, dY, dX1, dY1);
	}

	//画N横断面线
	for (int i = 0; i < 10; ++i)
	{
		dX = i * 1500.0 / 10.0;
		dY = (m_calcH.NHInsertPoint()[i].H() - 10) * 500.0 / 10.0;
		dX1 = (i + 1) * 1500.0 / 10.0;
		dY1 = (m_calcH.NHInsertPoint()[i + 1].H() - 10) * 500.0 / 10.0;
		m_dxf.Point(dX, dY);
		m_dxf.Line(dX, dY, dX1, dY1);
	}
	m_dxf.End();
}


void CSectionCalculationDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialog::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: Add your message handler code here


	ASSERT(pPopupMenu != NULL);
	// Check the enabled state of various menu items.
	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);
	// Determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup).
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		// Child windows don't have menus--need to go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// When popup is found, m_pParentMenu is containing menu.
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}
	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it.
		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// Possibly a popup menu, route to first item of that popup.
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // First item of popup can't be routed to.
			}
			state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
		}
		else
		{
			// Normal menu item.
			// Auto enable/disable if frame window has m_bAutoMenuEnable
			// set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}
		// Adjust for menu deletions and additions.
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}


BOOL CSectionCalculationDlg::OnToolTipNotify(UINT id, NMHDR * pNMHDR, LRESULT * pResult)
{
	TOOLTIPTEXT* pT = (TOOLTIPTEXT*)pNMHDR;	//将pNMHDR转换成TOOLTIPTEXT指针类型数据

	UINT nID = pNMHDR->idFrom;				//获取工具条上按钮的ID

	if (nID == IDM_OPEN)					//如果nID是希望获取的ID,那么就设置相应提示信息到TOOLTIPTEXT结构体的lpszText中。
	{
		pT->lpszText = _T("打开文件");
		pT->hinst = AfxGetResourceHandle();
		return(TRUE);
	}
	if (nID == IDM_VCALC)
	{
		pT->lpszText = _T("计算纵断面的信息");
		pT->hinst = AfxGetResourceHandle();
		return(TRUE);
	}
	if (nID == IDM_HCALC)
	{
		pT->lpszText = _T("计算纵断面的信息");
		pT->hinst = AfxGetResourceHandle();
		return(TRUE);
	}
	if (nID == IDM_DRAW)
	{
		pT->lpszText = _T("图形界面");
		pT->hinst = AfxGetResourceHandle();
		return(TRUE);
	}
	if (nID == IDM_REPORT)
	{
		pT->lpszText = _T("结果报表");
		pT->hinst = AfxGetResourceHandle();
		return(TRUE);
	}
	return FALSE;
}

void CSectionCalculationDlg::OnZoomIn()
{
	CZoomView::WheelScale(120);
	Invalidate();
}


void CSectionCalculationDlg::OnUpdateZoomIn(CCmdUI *pCmdUI)
{
	if (idd == 1)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}


void CSectionCalculationDlg::OnZoomOut()
{
	CZoomView::WheelScale(-120);
	Invalidate();
}


void CSectionCalculationDlg::OnUpdateZoomOut(CCmdUI *pCmdUI)
{
	if (idd == 1)
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}


BOOL CSectionCalculationDlg::ContinueModal()
{
	if (m_toolbar.IsWindowVisible())  // 如果对话框有工具栏,m_ToolBar为工具栏 
	{
		CFrameWnd* pParent = (CFrameWnd*)m_toolbar.GetParent();
		if (pParent)
			m_toolbar.OnUpdateCmdUI(pParent, (WPARAM)TRUE);
	}

	CMenu* pMainMenu = GetMenu();    // 如果对话框存在菜单,更新菜单 
	CCmdUI cmdUI;
	for (UINT n = 0; n < pMainMenu->GetMenuItemCount(); ++n)
	{
		CMenu* pSubMenu = pMainMenu->GetSubMenu(n);
		cmdUI.m_nIndexMax = pSubMenu->GetMenuItemCount();
		for (UINT i = 0; i < cmdUI.m_nIndexMax; ++i)
		{
			cmdUI.m_nIndex = i;
			cmdUI.m_nID = pSubMenu->GetMenuItemID(i);
			cmdUI.m_pMenu = pSubMenu;
			cmdUI.DoUpdate(this, FALSE);
		}
	}
	return CDialog::ContinueModal();
}
