#pragma once

///需要在父窗口的消息映射表中加入一条REFLECT_NOTIFICATIONS()宏，父窗口就能够将支持消息反射的控件所发出的消息反传回去
///添加CHAIN_MSG_MAP_ALT(COwnerDraw<CXKnowButton>, 1)，窗口默认的绘制消息WM_ERASEBKGND、WM_PRINT、WM_PRINTCLIENT就不会触发
class CXKnowButton : public CWindowImpl<CXKnowButton, CButton>,
	public COwnerDraw<CXKnowButton>
{
public:
	BEGIN_MSG_MAP(CXKnowButton)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouseHover)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CXKnowButton>, 1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
	
public:
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		if (!m_bTracking)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE | TME_HOVER;
			tme.dwHoverTime = 1;
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

		if (m_bOver)
		{
			if (nState & ODS_SELECTED)
			{
				m_hBmpTmp = m_hBmpPress;
			}
			else
			{
				m_hBmpTmp = m_hBmpHover;
			}
		}
		else
		{
			m_hBmpTmp = m_hBmpNormal;
		}

		

		HDC hMemDC = CreateCompatibleDC(hdc);
		
		//画背景
		HGDIOBJ hOldBmp = SelectObject(hMemDC, m_hBmpBkgnd);
		//画前景
		hOldBmp = SelectObject(hMemDC, m_hBmpTmp);
		BitBlt(hdc, 0, 0, rcItem.right - rcItem.left, rcItem.bottom - rcItem.top, hMemDC, 0, 0, SRCCOPY);
		SelectObject(hMemDC, hOldBmp);
		DeleteDC(hMemDC);
	}

	CXKnowButton()
	{
		m_hBmpNormal = CreateHBitmapFromFile(L"E:\\MyProject\\XKnow\\xknow\\xknow\\XKnowCtrl\\img\\50.png");
		m_hBmpHover = CreateHBitmapFromFile(L"E:\\MyProject\\XKnow\\xknow\\xknow\\XKnowCtrl\\img\\51.png");
		m_hBmpPress = CreateHBitmapFromFile(L"E:\\MyProject\\XKnow\\xknow\\xknow\\XKnowCtrl\\img\\52.png");

		m_hBmpBkgnd = NULL;
		m_bOver = FALSE;
		m_bTracking = FALSE;
	}
	~CXKnowButton()
	{
		DeleteObject(m_hBmpNormal);
		DeleteObject(m_hBmpHover);
		DeleteObject(m_hBmpPress);
	}

	void SetHBmpBkgnd(HBITMAP hBmp)
	{
		m_hBmpBkgnd = hBmp;
	}
private:
	HBITMAP m_hBmpNormal;
	HBITMAP m_hBmpHover;
	HBITMAP m_hBmpPress;
	HBITMAP m_hBmpDisable;
	HBITMAP m_hBmpTmp;
	HBITMAP m_hBmpBkgnd;

	BOOL m_bOver;
	BOOL m_bTracking;
};