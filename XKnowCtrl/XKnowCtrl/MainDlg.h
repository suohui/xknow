// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "XKnowPng.h"
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
		//MESSAGE_HANDLER(WM_PAINT, OnPaint)

		//MESSAGE_HANDLER(WM_SIZE, OnSize)

		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
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

		//SetWindowLong(GWL_STYLE, GetWindowLong(GWL_STYLE) & (~WS_BORDER) & WS_POPUP);//无边框窗体
		SetWindowLong(GWL_EXSTYLE, GetWindowLong(GWL_EXSTYLE) | WS_EX_APPWINDOW);    //显示在任务栏

		memset(szFileName, 0, MAX_PATH);
		memset(szBkgFileName, 0, MAX_PATH);
		GetModuleFileName(NULL, szFileName, MAX_PATH);

		PathRemoveFileSpec(szFileName);
		PathCombine(szBkgFileName, szFileName, _T("..\\img\\bkg.png"));

		XKnowPngInfo xi;
		xi.ReadPng(L"D:\\1.png");
		

		//PngLoadImage(szBkgFileName, &pbImage, &cxImgSize, &cyImgSize, &cImgChannels, &bkgColor);

		return TRUE;
	}
	TCHAR szFileName[MAX_PATH];
	TCHAR szBkgFileName[MAX_PATH];

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// unregister message filtering and idle updates
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		ATLASSERT(pLoop != NULL);
		pLoop->RemoveMessageFilter(this);
		pLoop->RemoveIdleHandler(this);

		return 0;
	}
	//无边框窗体可拖动
	LRESULT OnNcHitTest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		return HTCAPTION;
	}

	BYTE              *pbImage = NULL;
	int                cxWinSize, cyWinSize;
	unsigned int       cxImgSize, cyImgSize;
	int                cImgChannels;
	png_color          bkgColor = { 127, 127, 127 };
	
	LRESULT OnSize(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		int cxWinSize = LOWORD(lParam);
		int cyWinSize = HIWORD(lParam);

		/* invalidate the client area for later update */
		InvalidateRect(NULL, TRUE);

		/* display the PNG into the DIBitmap */
		BYTE              *pDib = NULL;
		BYTE              *pDiData = NULL;
		DisplayImage(m_hWnd, &pDib, &pDiData, cxWinSize, cyWinSize,
			pbImage, cxImgSize, cyImgSize, cImgChannels, TRUE);
		return 0;
	}

	void DoPaint(Graphics &g)
	{
		RECT rcClient;
		GetClientRect(&rcClient);
		Gdiplus::Rect rc(0, 0, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
		g.DrawImage(Image::FromFile(szBkgFileName), rc);
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		if (wParam != NULL)
		{
			Graphics g((HDC)wParam);
			DoPaint(g);
		}
		else
		{
			CPaintDC dc(m_hWnd);
			Graphics g(dc.m_hDC);
			DoPaint(g);
		}
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
		CloseDialog(wID);
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
