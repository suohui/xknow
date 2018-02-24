#pragma once

///需要在父窗口的消息映射表中加入一条REFLECT_NOTIFICATIONS()宏，父窗口就能够将支持消息反射的控件所发出的消息反传回去
///添加CHAIN_MSG_MAP_ALT(COwnerDraw<CXKnowButton>, 1)，窗口默认的绘制消息WM_ERASEBKGND、WM_PRINT、WM_PRINTCLIENT就不会触发
class CXKnowButton : public CWindowImpl<CXKnowButton, CButton>,
	public COwnerDraw<CXKnowButton>
{
public:
	BEGIN_MSG_MAP(CXKnowButton)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouseHover)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CXKnowButton>, 1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
	
public:
	LRESULT OnSetCursor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if (m_bHandCursor)
		{
			::SetCursor(::LoadCursor(NULL, IDC_HAND));
		}
		return 0;
	}
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if (!m_bTracking)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE | TME_HOVER;
			tme.dwHoverTime = 10;
			tme.hwndTrack = m_hWnd;
			m_bTracking = ::_TrackMouseEvent(&tme);
		}
		return 0;
	}
	LRESULT OnMouseHover(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_bOver = TRUE;
		InvalidateRect(NULL);
		return 0;
	}
	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_bOver = FALSE;
		m_bTracking = FALSE;
		InvalidateRect(NULL, FALSE);
		return 0;
	}
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		HDC hdc = lpDrawItemStruct->hDC;
		RECT rcItem = lpDrawItemStruct->rcItem;
		UINT nState = lpDrawItemStruct->itemState;

		CRect rcRectTmp;
		HBITMAP hBmpTmp = NULL;

		if (nState & ODS_DISABLED)
		{
			hBmpTmp = m_hBmpDisabled;
			rcRectTmp = m_rcDisabled;
		}
		else
		{
			if (m_bOver)
			{
				if (nState & ODS_SELECTED)
				{
					hBmpTmp = m_hBmpPress;
					rcRectTmp = m_rcPress;
				}
				else
				{
					hBmpTmp = m_hBmpHover;
					rcRectTmp = m_rcHover;
				}
			}
			else
			{
				hBmpTmp = m_hBmpNormal;
				rcRectTmp = m_rcNormal;
			}
		}

		BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

		//画背景
		HDC hMemDCBkg = CreateCompatibleDC(hdc);
		HGDIOBJ hOldBmp = SelectObject(hMemDCBkg, m_hBmpBkgnd);
		RECT rcWindow;
		GetWindowRect(&rcWindow);
		::MapWindowPoints(NULL, GetParent().m_hWnd, (LPPOINT)(LPRECT)&rcWindow, 2);	//获得其在父窗体上的坐标
		BitBlt(hdc, 0, 0, rcItem.right - rcItem.left, rcItem.bottom - rcItem.top, hMemDCBkg, rcWindow.left, rcWindow.top, SRCCOPY);
		SelectObject(hMemDCBkg, hOldBmp);
		DeleteDC(hMemDCBkg);
		//画前景
		HDC hMemDC = CreateCompatibleDC(hdc);
		if (NULL != hBmpTmp)
		{
			hOldBmp = SelectObject(hMemDC, hBmpTmp);
			//画文字
			DrawText(hMemDC, L"重启电脑", lstrlen(L"重启电脑"), &rcRectTmp, DT_CENTER | DT_VCENTER);
			AlphaBlend(hdc, 0, 0, rcItem.right - rcItem.left, rcItem.bottom - rcItem.top, hMemDC, 0, 0, rcItem.right - rcItem.left, rcItem.bottom - rcItem.top, bf);
		}
		else
		{
			hOldBmp = SelectObject(hMemDC, m_hBmpAllInOne);
			//画文字
			CFont font;
			font.CreateFont(
				20,                        // nHeight
				0,                         // nWidth
				0,                         // nEscapement
				0,                         // nOrientation
				FW_NORMAL,                 // nWeight
				FALSE,                     // bItalic
				FALSE,                     // bUnderline
				0,                         // cStrikeOut
				ANSI_CHARSET,              // nCharSet
				OUT_DEFAULT_PRECIS,        // nOutPrecision
				CLIP_DEFAULT_PRECIS,       // nClipPrecision
				DEFAULT_QUALITY,           // nQuality
				DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
				_T("微软雅黑"));                 // lpszFacename
			//ft.CreatePointFont(120, L"微软雅黑", hdc);
			HGDIOBJ hold = SelectObject(hMemDC, font.m_hFont);
			::SetBkMode(hMemDC, TRANSPARENT);
			SetTextColor(hMemDC, RGB(122, 122, 122));
			DrawText(hMemDC, L"立即重启", -1, &rcRectTmp, DT_CENTER | DT_VCENTER);

			AlphaBlend(hdc, 0, 0, rcItem.right - rcItem.left, rcItem.bottom - rcItem.top, hMemDC, rcRectTmp.left, rcRectTmp.top, rcRectTmp.Width(), rcRectTmp.Height(), bf);
			SelectObject(hMemDC, hold);
		}

		SelectObject(hMemDC, hOldBmp);
		DeleteDC(hMemDC);
	}

	CXKnowButton()
	{
		m_hBmpNormal = NULL;
		m_hBmpHover = NULL;
		m_hBmpPress = NULL;
		m_hBmpDisabled = NULL;

		m_hBmpBkgnd = NULL;
		m_bOver = FALSE;
		m_bTracking = FALSE;

		m_bHandCursor = FALSE;
	}
	~CXKnowButton()
	{
		DeleteObject(m_hBmpNormal);
		m_hBmpNormal = NULL;
		if (m_hBmpHover != NULL)
		{
			DeleteObject(m_hBmpHover);
			m_hBmpHover = NULL;
		}
		if (m_hBmpPress != NULL)
		{
			DeleteObject(m_hBmpPress);
			m_hBmpPress = NULL;
		}
		if (m_hBmpDisabled != NULL)
		{
			DeleteObject(m_hBmpDisabled);
			m_hBmpDisabled = NULL;
		}
	}

	void SetHBmpBkgnd(HBITMAP hBmp)
	{
		m_hBmpBkgnd = hBmp;
	}

	void SetImage(LPCTSTR lpszNormalFileName, LPCTSTR lpszHoverFileName = NULL, LPCTSTR lpszPressFileName = NULL, LPCTSTR lpszDisabledFileName = NULL)
	{
		m_hBmpNormal = CreateHBitmapFromFile(lpszNormalFileName);
		m_hBmpHover = m_hBmpNormal;
		m_hBmpPress = m_hBmpNormal;
		m_hBmpDisabled = m_hBmpNormal;
		if (lpszHoverFileName != NULL)
		{
			m_hBmpHover = CreateHBitmapFromFile(lpszHoverFileName);
			m_hBmpPress = m_hBmpHover;
			if (lpszPressFileName != NULL)
			{
				m_hBmpPress = CreateHBitmapFromFile(lpszPressFileName);
				if (lpszDisabledFileName != NULL)
				{
					m_hBmpDisabled = CreateHBitmapFromFile(lpszDisabledFileName);
				}
			}
		}
	}

	void SetImage(LPCTSTR lpszFileName, PNGTYPE type)
	{
		m_hBmpAllInOne = CreateHBitmapFromFile(lpszFileName, m_iWidth, m_iHeight, m_bAlpha);
		if (type == PNGTYPE::TwoInOne)
		{
			m_rcNormal.SetRect(0, 0, m_iWidth / 2, m_iHeight);
			m_rcHover.SetRect(m_iWidth / 2, 0, m_iWidth, m_iHeight);
			m_rcPress = m_rcHover;
			m_rcDisabled = m_rcNormal;
		}
		else if (type == PNGTYPE::ThreeInOne)
		{
			m_rcNormal.SetRect(0, 0, m_iWidth / 3, m_iHeight);
			m_rcHover.SetRect(m_iWidth  / 3, 0, m_iWidth * 2 / 3, m_iHeight);
			m_rcPress.SetRect(m_iWidth * 2 / 3, 0, m_iWidth, m_iHeight);
			m_rcDisabled = m_rcNormal;
		}
		else if (type == PNGTYPE::FourInOne)
		{
			m_rcNormal.SetRect(0, 0, m_iWidth / 4, m_iHeight);
			m_rcHover.SetRect(m_iWidth / 4, 0, m_iWidth * 2 / 4, m_iHeight);
			m_rcPress.SetRect(m_iWidth * 2 / 4, 0, m_iWidth * 3 / 4, m_iHeight);
			m_rcDisabled.SetRect(m_iWidth * 3 / 4, 0, m_iWidth, m_iHeight);
		}
	}
	
	void SetHandCursor()
	{
		m_bHandCursor = TRUE;
	}
private:
	HBITMAP m_hBmpNormal;
	HBITMAP m_hBmpHover;
	HBITMAP m_hBmpPress;
	HBITMAP m_hBmpDisabled;
	HBITMAP m_hBmpBkgnd;

	int m_iWidth;
	int m_iHeight;
	BOOL m_bAlpha;
	HBITMAP m_hBmpAllInOne;
	CRect m_rcNormal;
	CRect m_rcHover;
	CRect m_rcPress;
	CRect m_rcDisabled;

	BOOL m_bOver;
	BOOL m_bTracking;

	BOOL m_bHandCursor;
};