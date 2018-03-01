#pragma once

template <class T>
class CXKnowDlgBase : public CMessageMap,
					  public CXKnowTextBase,
					  public CXKnowIconBase
{
public:
	CXKnowDlgBase()
	{
		m_pBkgndImageInfo = NULL;
	}
	~CXKnowDlgBase()
	{
		CXKnowRender::FreeImage(m_pBkgndImageInfo);
	}

	void SetBkgndFilePath(String strFilePath)
	{
		m_pBkgndImageInfo = CXKnowRender::LoadImageFromFile(strFilePath);
	}

	BEGIN_MSG_MAP(CXKnowDlgBase)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pThis = static_cast<T*>(this);
		pThis->SetMsgHandled(TRUE);

		//修改窗体属性
		pThis->SetWindowLong(GWL_STYLE, pThis->GetWindowLong(GWL_STYLE) & (~WS_BORDER) & WS_POPUP);//无边框窗体
		pThis->SetWindowLong(GWL_EXSTYLE, pThis->GetWindowLong(GWL_EXSTYLE) | WS_EX_APPWINDOW);    //显示在任务栏
		//窗体的初始化工作，子类不再响应WM_INITDIALOG，只用重写InitDialog()函数就可以了
		pThis->InitDialog();

		bHandled = pThis->IsMsgHandled();
		return (LRESULT)TRUE;
	}
	// Overrideables
	void InitDialog()
	{
		// must be implemented
		ATLASSERT(FALSE);
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pThis = static_cast<T*>(this);
		CPaintDC dcPaint(pThis->m_hWnd);
		CRect rcClient;
		pThis->GetClientRect(&rcClient);
		
		CMemoryDC dcMem(dcPaint, rcClient);
		//画背景
		CXKnowRender::DrawImage(dcMem, rcClient, m_pBkgndImageInfo->hBitmap, CRect(0, 0, m_pBkgndImageInfo->iWidth, m_pBkgndImageInfo->iHeight), FALSE, FALSE);
		//画LOGO
		if (m_pIconImageInfo != NULL && !m_rcIcon.IsRectNull())
		{
			CXKnowRender::DrawImage(dcMem, m_rcIcon, m_pIconImageInfo->hBitmap, CRect(0, 0, m_pIconImageInfo->iWidth, m_pIconImageInfo->iHeight), m_pIconImageInfo->bAlpha, FALSE);
		}
		//画Title
		CXKnowRender::DrawText(dcMem, m_strText, m_rcText, m_dwTextNormalColor, m_strFontID, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);

		return 0;
	}

	//无边框窗体可拖动
	LRESULT OnNcHitTest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		return HTCAPTION;
	}
protected:
	//背景
	XKnowImageInfo* m_pBkgndImageInfo;
};
