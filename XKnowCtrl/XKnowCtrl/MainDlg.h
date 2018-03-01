// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
//1���ޱ߿��塢���϶�
//2����LOGO�����⡢����
//3����������Ӱ
//4������Ť
//5��������
//6����Label
class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler,
		public CXKnowDlgBase<CMainDlg>
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
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)

		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColorStatic)

		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		
		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(CXKnowDlgBase)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	void InitDialog()
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
		//��ȡͼƬ·��
		TCHAR szExePath[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, szExePath, MAX_PATH);
		PathRemoveFileSpec(szExePath);
		TCHAR szImagePath[MAX_PATH] = { 0 };
		PathCombine(szImagePath, szExePath, _T("..\\img\\"));
		m_strImageDir = szImagePath;
		//��ȡ����ͼƬ
		SetBkgndFilePath(m_strImageDir + _T("bkg.png"));
		SetIconFilePath(m_strImageDir + _T("logo.png"));
		SetIconRect(CRect(22, 12, 22 + 167, 12 + 32));
		SetText(L"��Ƶ�绰");
		SetTextRect(CRect(200, 10, 250, 30));
		//����LOGO
		CStatic logoWnd = (CStatic)GetDlgItem(IDC_LOGO);
		
		//m_hLogoBmp = CreateHBitmapFromFile((m_strImageDir + _T("logo.png")).c_str());
		//logoWnd.ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ������λ����ʾʹ����
		//logoWnd.SetBitmap(m_hLogoBmp);
		//logoWnd.MoveWindow(180+22, 12, 167, 32);


		//���ð�ť
		m_MenuBtn.SubclassWindow(GetDlgItem(IDC_MENU).m_hWnd);	//SubclassWindowֻ��CreateWindowʱ��Ч
		m_MenuBtn.SetBkgndBitmap(m_pBkgndImageInfo->hBitmap);
		m_MenuBtn.SetImageFilePath(m_strImageDir + _T("menu.png"), PNGTYPE::ThreeInOne);
		m_MenuBtn.MoveWindow(680 - 12 - 6 * 2 - 28 * 3, 14, 28, 28);
		m_MenuBtn.SetHandCursor();

		m_MinBtn.SubclassWindow(GetDlgItem(IDC_MIN).m_hWnd);	//SubclassWindowֻ��CreateWindowʱ��Ч
		m_MinBtn.SetBkgndBitmap(m_pBkgndImageInfo->hBitmap);
		m_MinBtn.SetImageFilePath(m_strImageDir + _T("min.png"), PNGTYPE::ThreeInOne);
		m_MinBtn.MoveWindow(680 - 12 - 6 - 28 * 2, 14, 28, 28);
		m_MinBtn.SetHandCursor();

		m_CloseBtn.SubclassWindow(GetDlgItem(IDOK).m_hWnd);	//SubclassWindowֻ��CreateWindowʱ��Ч
		m_CloseBtn.SetBkgndBitmap(m_pBkgndImageInfo->hBitmap);
		m_CloseBtn.SetImageFilePath(m_strImageDir + _T("close.png"), PNGTYPE::ThreeInOne);
		m_CloseBtn.MoveWindow(680 - 12 - 28, 14, 28, 28);
		m_CloseBtn.SetHandCursor();

		m_RebootBtn.SubclassWindow(GetDlgItem(IDC_REBOOT).m_hWnd);	//SubclassWindowֻ��CreateWindowʱ��Ч
		m_RebootBtn.SetBkgndBitmap(m_pBkgndImageInfo->hBitmap);
		m_RebootBtn.SetImageFilePath(m_strImageDir + _T("btn.png"), PNGTYPE::FourInOne);
		m_RebootBtn.MoveWindow(100, 200, 160, 32);
		m_RebootBtn.SetHandCursor();
		m_RebootBtn.SetText(L"��������");

		m_lblTest.SubclassWindow(GetDlgItem(IDC_LABELTEST).m_hWnd);
		m_lblTest.SetBkgndBitmap(m_pBkgndImageInfo->hBitmap);
		m_lblTest.SetText(_T("������SubclassWindowSubclassWindowSubclassWindow"));
		m_lblTest.SetControlPos(50, 150, 100, 20);

		m_AboutBtn.SubclassWindow(GetDlgItem(ID_APP_ABOUT).m_hWnd);
		m_AboutBtn.SetBkgndBitmap(m_pBkgndImageInfo->hBitmap);
		m_AboutBtn.SetImageFilePath(m_strImageDir + _T("test.png"), PNGTYPE::ThreeInOne);
		m_AboutBtn.MoveWindow(425, 10, 42, 60);
		m_AboutBtn.SetHandCursor();
		m_AboutBtn.SetText(L"����");
		m_AboutBtn.SetTextRect(CRect(0, 42, 42, 60));
	}
	String m_strImageDir; //ͼƬ·����ĩβ��//

	CXKnowButton m_MenuBtn;
	CXKnowButton m_MinBtn;
	CXKnowButton m_CloseBtn;

	CXKnowButton m_RebootBtn;

	CXKnowButton m_AboutBtn;

	CXKnowLabel m_lblTest;


	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);
		return 0;
	}
	
	LRESULT OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));
	}

	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
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
