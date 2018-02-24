// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
//1、无边框窗体、可拖动
//2、画LOGO、标题、背景
//3、画窗体阴影
//4、画按扭
//5、画动画
//6、画Label
class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler
{
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CWindow::IsDialogMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		UIUpdateChildWindows();
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)

		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColorStatic)

		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)

		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		MoveWindow(0, 0, 681, 451);
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
		SetIcon(hIconSmall, FALSE);

		// register object for message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);

		UIAddChildWindowContainer(m_hWnd);
		//修改窗体属性
		SetWindowLong(GWL_STYLE, GetWindowLong(GWL_STYLE) & (~WS_BORDER) & WS_POPUP);//无边框窗体
		SetWindowLong(GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_APPWINDOW);    //显示在任务栏
		//获取背景图片
		memset(szImageDir, 0, MAX_PATH);
		memset(szBkgFileName, 0, MAX_PATH);
		GetModuleFileName(NULL, szImageDir, MAX_PATH);
		PathRemoveFileSpec(szImageDir);
		PathCombine(szImageDir, szImageDir, _T("..\\img"));
		PathCombine(szBkgFileName, szImageDir, _T("bkg.png"));
		m_hBkgndBmp = CreateHBitmapFromFile(szBkgFileName);

		//设置LOGO
		CStatic logoWnd = (CStatic)GetDlgItem(IDC_LOGO);
		TCHAR szLogoFile[MAX_PATH] = { 0 };
		PathCombine(szLogoFile, szImageDir, _T("logo.png"));
		m_hLogoBmp = CreateHBitmapFromFile(szLogoFile);
		logoWnd.ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);//设置静态控件的样式，使其可以使用位图，并试位标显示使居中
		logoWnd.SetBitmap(m_hLogoBmp);
		logoWnd.MoveWindow(22, 12, 167, 32);


		//设置按钮
		m_MenuBtn.SubclassWindow(GetDlgItem(IDC_MENU).m_hWnd);	//SubclassWindow只对CreateWindow时有效
		m_MenuBtn.ModifyStyle(0, BS_OWNERDRAW); //设置BS_OWNERDRAW样式
		m_MenuBtn.SetHBmpBkgnd(m_hBkgndBmp);
		TCHAR szMenuBtnFile[MAX_PATH] = { 0 };
		PathCombine(szMenuBtnFile, szImageDir, _T("menu.png"));
		m_MenuBtn.SetImage(szMenuBtnFile, PNGTYPE::ThreeInOne);
		m_MenuBtn.MoveWindow(680 - 12 - 6 * 2 - 28 * 3, 14, 28, 28);
		m_MenuBtn.SetHandCursor();

		m_MinBtn.SubclassWindow(GetDlgItem(IDC_MIN).m_hWnd);	//SubclassWindow只对CreateWindow时有效
		m_MinBtn.ModifyStyle(0, BS_OWNERDRAW); //设置BS_OWNERDRAW样式
		m_MinBtn.SetHBmpBkgnd(m_hBkgndBmp);
		TCHAR szMinBtnFile[MAX_PATH] = { 0 };
		PathCombine(szMinBtnFile, szImageDir, _T("min.png"));
		m_MinBtn.SetImage(szMinBtnFile, PNGTYPE::ThreeInOne);
		m_MinBtn.MoveWindow(680 - 12 - 6 - 28 * 2, 14, 28, 28);
		m_MinBtn.SetHandCursor();

		m_CloseBtn.SubclassWindow(GetDlgItem(IDOK).m_hWnd);	//SubclassWindow只对CreateWindow时有效
		m_CloseBtn.ModifyStyle(0, BS_OWNERDRAW); //设置BS_OWNERDRAW样式
		m_CloseBtn.SetHBmpBkgnd(m_hBkgndBmp);
		TCHAR szCloseBtnFile[MAX_PATH] = { 0 };
		PathCombine(szCloseBtnFile, szImageDir, _T("close.png"));
		m_CloseBtn.SetImage(szCloseBtnFile, PNGTYPE::ThreeInOne);
		m_CloseBtn.MoveWindow(680 - 12 - 28, 14, 28, 28);
		m_CloseBtn.SetHandCursor();

		m_RebootBtn.SubclassWindow(GetDlgItem(IDC_REBOOT).m_hWnd);	//SubclassWindow只对CreateWindow时有效
		m_RebootBtn.ModifyStyle(0, BS_OWNERDRAW); //设置BS_OWNERDRAW样式
		m_RebootBtn.SetHBmpBkgnd(m_hBkgndBmp);
		TCHAR szRebootBtnFile[MAX_PATH] = { 0 };
		PathCombine(szRebootBtnFile, szImageDir, _T("btn.png"));
		m_RebootBtn.SetImage(szRebootBtnFile, PNGTYPE::FourInOne);
		m_RebootBtn.MoveWindow(100, 200, 160, 32);
		m_RebootBtn.SetHandCursor();

		

		return TRUE;
	}
	TCHAR szImageDir[MAX_PATH];
	TCHAR szBkgFileName[MAX_PATH];

	HBITMAP m_hLogoBmp;
	HBITMAP m_hBkgndBmp;

	CXKnowButton m_MenuBtn;
	CXKnowButton m_MinBtn;
	CXKnowButton m_CloseBtn;

	CXKnowButton m_RebootBtn;

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		DeleteObject(m_hLogoBmp);
		DeleteObject(m_hBkgndBmp);

		return 0;
	}
	//无边框窗体可拖动
	LRESULT OnNcHitTest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		return HTCAPTION;
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		CPaintDC dc(m_hWnd);
		HDC hMemDC = CreateCompatibleDC(dc.m_hDC);
		HGDIOBJ hOld = SelectObject(hMemDC, m_hBkgndBmp);
		RECT rcClient;
		GetClientRect(&rcClient);
		BitBlt(dc.m_hDC, 0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top, hMemDC, 0, 0, SRCCOPY);

		SelectObject(hMemDC, hOld);
		DeleteDC(hMemDC);
		return 0;
	}
	
	LRESULT OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CStatic lbl = (CStatic)GetDlgItem(IDC_LABELTEST);
		
		//lbl.SetWindowText(L"已加载");
		

		CFont ft;
		//ft.CreatePointFont(12, L"宋体", lbl.GetDC(), true, true);
		ft.CreateFont(12, 0, 0, 0, FW_NORMAL, TRUE, TRUE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
			OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"微软雅黑");
		lbl.SetFont(ft.m_hFont);
		::SetTextColor(lbl.GetDC(), RGB(255, 0, 255));
		lbl.ShowWindow(SW_HIDE);
		lbl.ShowWindow(SW_SHOW);

		lbl.GetFont();

		//CAboutDlg dlg;
		//dlg.DoModal();
		return 0;
	}

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		// TODO: Add validation code 
		//CloseDialog(wID);
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CloseDialog(wID);
		return 0;
	}

	void CloseDialog(int nVal)
	{
		DestroyWindow();
		::PostQuitMessage(nVal);
	}
};
