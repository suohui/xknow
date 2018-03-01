#pragma once

//文字信息基础类
class CXKnowTextBase
{
public:
	CXKnowTextBase()
	{
		//设置默认字体ID
		m_strFontID[0] = CXKnowGobal::GetNormalFontID();
		m_strFontID[1] = CXKnowGobal::GetHoverFontID();
		m_strFontID[2] = CXKnowGobal::GetPressFontID();
		m_strFontID[3] = CXKnowGobal::GetDisabledFontID();
		//设置默认字体颜色
		m_dwTextColor[0] = CXKnowGobal::GetNormalTextColor();
		m_dwTextColor[1] = CXKnowGobal::GetHoverTextColor();
		m_dwTextColor[2] = CXKnowGobal::GetPressTextColor();
		m_dwTextColor[3] = CXKnowGobal::GetDisabledTextColor();
		//设置默认字体绘制样式
		m_uFormatStyle = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS;
		m_bMultiLine = FALSE;
	}

	void SetText(String strText, BOOL bMultiLine = FALSE)
	{
		m_strText = strText;
		m_bMultiLine = bMultiLine;
	}

	void SetTextColor(DWORD dwTextNormalColor, DWORD dwTextHoverColor = -1, DWORD dwTextPressColor = -1, DWORD dwTextDisableColor = -1)
	{
		m_dwTextColor[0] = dwTextNormalColor;
		if (dwTextHoverColor != -1)
		{
			m_dwTextColor[1] = dwTextHoverColor;
			if (dwTextPressColor != -1)
			{
				m_dwTextColor[2] = dwTextPressColor;
				if (dwTextDisableColor != -1)
				{
					m_dwTextColor[3] = dwTextDisableColor;
				}
			}
		}
	}

	void SetTextFontID(String strNormal, String strHover = _T(""), String strPress = _T(""), String strDisable = _T(""))
	{
		m_strFontID[0] = strNormal;
		if (!strHover.empty())
		{
			m_strFontID[1] = strHover;
			if (!strPress.empty())
			{
				m_strFontID[2] = strPress;
				if (!strDisable.empty())
				{
					m_strFontID[3] = strDisable;
				}
			}
		}
	}

	void SetTextRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcText.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}

	void SetTextFormatStyle(UINT uStyle)
	{
		m_uFormatStyle = uStyle;
	}

	void SetTextMultiLine(BOOL bMultiLine)
	{
		m_bMultiLine = bMultiLine;
	}

protected:
	String m_strText;	//文字内容
	CRect m_rcText;	//文字绘制矩形框
	UINT  m_uFormatStyle; //文字绘制样式
	BOOL m_bMultiLine;	//多行。简单起见，单行默认的绘制样式为DT_CENTER | DT_VCENTER | DT_SINGLELINE
	DWORD m_dwTextColor[4];//字体颜色
	String m_strFontID[4]; //字体ID
};
//Icon图标信息基础类，单一图片信息，例如：按钮上的标识图标、窗体LOGO，
class CXKnowIconBase
{
public:
	CXKnowIconBase()
	{
		m_pIconImageInfo = NULL;
	}
	~CXKnowIconBase()
	{
		CXKnowRender::FreeImage(m_pIconImageInfo);
	}

	void SetIconFilePath(String strIconFilePath)
	{
		m_pIconImageInfo = CXKnowRender::LoadImageFromFile(strIconFilePath);
	}

	void SetIconRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcIcon.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}
protected:
	XKnowImageInfo * m_pIconImageInfo;
	CRect m_rcIcon;
};

//图片信息基础类，2-4态多图组合，例如：按钮
class CXKnowImageBase
{
public:
	CXKnowImageBase()
	{
		m_pImageInfo = NULL;
	}
	~CXKnowImageBase()
	{
		CXKnowRender::FreeImage(m_pImageInfo);
	}

	void SetImageFilePath(String strImageFilePath, PNGTYPE type)
	{
		m_pImageInfo = CXKnowRender::LoadImageFromFile(strImageFilePath);
		int iWidth = m_pImageInfo->iWidth;
		int iHeight = m_pImageInfo->iHeight;
		if (type == PNGTYPE::TwoInOne)
		{
			m_rcImageRect[0].SetRect(0, 0, iWidth / 2, iHeight);
			m_rcImageRect[1].SetRect(iWidth / 2, 0, iWidth, iHeight);
			m_rcImageRect[2] = m_rcImageRect[1];
			m_rcImageRect[3] = m_rcImageRect[0];
		}
		else if (type == PNGTYPE::ThreeInOne)
		{
			m_rcImageRect[0].SetRect(0, 0, iWidth / 3, iHeight);
			m_rcImageRect[1].SetRect(iWidth / 3, 0, iWidth * 2 / 3, iHeight);
			m_rcImageRect[2].SetRect(iWidth * 2 / 3, 0, iWidth, iHeight);
			m_rcImageRect[3] = m_rcImageRect[0];
		}
		else if (type == PNGTYPE::FourInOne)
		{
			m_rcImageRect[0].SetRect(0, 0, iWidth / 4, iHeight);
			m_rcImageRect[1].SetRect(iWidth / 4, 0, iWidth * 2 / 4, iHeight);
			m_rcImageRect[2].SetRect(iWidth * 2 / 4, 0, iWidth * 3 / 4, iHeight);
			m_rcImageRect[3].SetRect(iWidth * 3 / 4, 0, iWidth, iHeight);
		}
	}
protected:
	XKnowImageInfo * m_pImageInfo;
	CRect m_rcImageRect[4];
};

template <class T>
class CXKnowControlBase : public CMessageMap
{
public:
	CXKnowControlBase()
	{
		m_hBkgndBmp = NULL;
		m_dwBkgndColor = 0;
		m_bOver = FALSE;
		m_bTracking = FALSE;
		m_bMouseDown = FALSE;
		m_bHandCursor = FALSE;
	}
	~CXKnowControlBase()
	{
		//
	}

	BEGIN_MSG_MAP(CXKnowControlBase)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouseHover)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	END_MSG_MAP()
public:
	//设置控件背景图片
	void SetBkgndBitmap(HBITMAP hBmp)
	{
		m_hBkgndBmp = hBmp;
	}
	//设置控件背景颜色
	void SetBkgndColor(DWORD dwColor)
	{
		m_dwBkgndColor = dwColor;
		T* pThis = static_cast<T*>(this);
		pThis->InvalidateRect(NULL, FALSE);
	}
	//设置控件位置
	void SetControlPos(int iLeft, int iTop, int iWidth, int iHeight)
	{
		T* pThis = static_cast<T*>(this);
		pThis->MoveWindow(iLeft, iTop, iWidth, iHeight);
	}
	//设置控件手型鼠标
	void SetHandCursor()
	{
		m_bHandCursor = TRUE;
	}

	// Overrideables//底色或背景已经处理好了，只需要绘制控件特有内容即可
	void DoPaint(HDC, CRect, int iStateIndex)
	{
		// must be implemented
		ATLASSERT(FALSE);
	}
protected:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pThis = static_cast<T*>(this);
		CRect rcClient;
		pThis->GetClientRect(&rcClient);

		CPaintDC dc(pThis->m_hWnd);
		CMemoryDC memDC(dc, rcClient);
		if (0 != m_dwBkgndColor)
			CXKnowRender::DrawColor(memDC, rcClient, m_dwBkgndColor);
		if (NULL != m_hBkgndBmp)
			CXKnowRender::DrawBkgnd(pThis->m_hWnd, memDC, rcClient, m_hBkgndBmp);
		int iStateIndex = pThis->IsWindowEnabled() ? 0 : 3;
		if (m_bMouseDown)
			iStateIndex = 2;
		else if (m_bOver)
			iStateIndex = 1;
		pThis->DoPaint(memDC, rcClient, iStateIndex);
		return 0;
	}

	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if (!m_bTracking)
		{
			T* pThis = static_cast<T*>(this);
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE | TME_HOVER;
			tme.dwHoverTime = 10;
			tme.hwndTrack = pThis->m_hWnd;
			m_bTracking = ::_TrackMouseEvent(&tme);
		}
		return 0;
	}
	LRESULT OnMouseHover(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pThis = static_cast<T*>(this);
		m_bOver = TRUE;
		pThis->InvalidateRect(NULL);
		return 0;
	}
	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pThis = static_cast<T*>(this);
		m_bOver = FALSE;
		m_bTracking = FALSE;
		pThis->InvalidateRect(NULL, FALSE);
		return 0;
	}
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_bMouseDown = TRUE;
		T* pThis = static_cast<T*>(this);
		pThis->SetCapture();	//在通常情况下，只有当鼠标位于窗体内时，窗体才能接收到鼠标的消息。如果需要接收所有的鼠标消息而不论鼠标是否在窗口内，这时可以调用SetCapture函数来实现
		pThis->InvalidateRect(NULL, FALSE);
		return 0;
	}
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		::ReleaseCapture();
		m_bMouseDown = FALSE;
		T* pThis = static_cast<T*>(this);
		pThis->InvalidateRect(NULL, FALSE);
		return 0;
	}
	LRESULT OnSetCursor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if (m_bHandCursor)
		{
			::SetCursor(::LoadCursor(NULL, IDC_HAND));
		}
		return 0;
	}
protected:
	HBITMAP m_hBkgndBmp;	//控件背景图片句柄
	DWORD m_dwBkgndColor;	//控件背景颜色

	BOOL m_bOver;
	BOOL m_bTracking;
	BOOL m_bMouseDown;
	BOOL m_bHandCursor;
};