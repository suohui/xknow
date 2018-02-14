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
		memset(szFileName, 0, MAX_PATH);
		memset(szBkgFileName, 0, MAX_PATH);
		GetModuleFileName(NULL, szFileName, MAX_PATH);
		PathRemoveFileSpec(szFileName);
		PathCombine(szBkgFileName, szFileName, _T("..\\img\\bkg.png"));
		m_hBkgndBmp = CreateHBitmapFromFile(szBkgFileName);

		m_AboutBtn.SubclassWindow(GetDlgItem(IDOK).m_hWnd);	//SubclassWindow只对CreateWindow时有效
		m_AboutBtn.ModifyStyle(0, BS_OWNERDRAW); //设置BS_OWNERDRAW样式
		m_AboutBtn.SetHBmpBkgnd(m_hBkgndBmp);
		m_AboutBtn.SetImage(L"D:\\XKnow\\xknow\\xknow\\XKnowCtrl\\img\\50.png", L"D:\\XKnow\\xknow\\xknow\\XKnowCtrl\\img\\51.png");
		//m_AboutBtn.SetImage(L"C:\\Users\\suo\\Desktop\\开心矿场\\开心矿场 切图\\1  主界面\\提币.png", PNGTYPE::FourInOne);
		m_AboutBtn.MoveWindow(100, 100, 64, 64);
		m_AboutBtn.SetHandCursor();

		return TRUE;
	}
	TCHAR szFileName[MAX_PATH];
	TCHAR szBkgFileName[MAX_PATH];

	HBITMAP m_hBkgndBmp;

	CXKnowButton m_AboutBtn;

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

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

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CAboutDlg dlg;
		dlg.DoModal();
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
