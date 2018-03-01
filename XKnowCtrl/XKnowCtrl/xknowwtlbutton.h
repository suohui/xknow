#pragma once

///需要在父窗口的消息映射表中加入一条REFLECT_NOTIFICATIONS()宏，父窗口就能够将支持消息反射的控件所发出的消息反传回去
///添加CHAIN_MSG_MAP_ALT(COwnerDraw<CXKnowButton>, 1)，窗口默认的绘制消息WM_ERASEBKGND、WM_PRINT、WM_PRINTCLIENT就不会触发
class CXKnowWTLButton : public CWindowImpl<CXKnowWTLButton, CButton>,
	public COwnerDraw<CXKnowWTLButton>,
	public CXKnowTextBase,
	public CXKnowImageBase,
	public CXKnowControlBase<CXKnowWTLButton>
{
public:
	BEGIN_MSG_MAP(CXKnowWTLButton)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouseHover)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		CHAIN_MSG_MAP_ALT(COwnerDraw<CXKnowWTLButton>, 1)
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
		CRect rcItem = lpDrawItemStruct->rcItem;
		UINT nState = lpDrawItemStruct->itemState;

		int iStateIndex = 0;
		if (nState & ODS_DISABLED)
		{
			iStateIndex = 3;
		}
		else
		{
			if (m_bOver)
			{
				if (nState & ODS_SELECTED)
				{
					iStateIndex = 2;
				}
				else
				{
					iStateIndex = 1;
				}
			}
		}
		//双缓冲绘图
		CMemoryDC memDC(hdc, rcItem);
		//画背景
		CXKnowRender::DrawBkgnd(m_hWnd, memDC, rcItem, m_hBkgndBmp);
		//画前景
		CXKnowRender::DrawImage(memDC, rcItem, m_pImageInfo->hBitmap, m_rcImageRect[iStateIndex], m_pImageInfo->bAlpha);
		//画文字
		//CXKnowRender::DrawText(memDC, m_strText, m_rcText.IsRectNull() ? rcItem : m_rcText, m_dwTextColor[iStateIndex], m_strFontID, m_uFormatStyle);
	}

	CXKnowWTLButton()
	{
		m_bOver = FALSE;
		m_bTracking = FALSE;
		m_bHandCursor = FALSE;
	}
	~CXKnowWTLButton()
	{
	}

	void SetHandCursor()
	{
		m_bHandCursor = TRUE;
	}

	BOOL SubclassWindow(HWND hWnd)
	{
		//SubclassWindow只对CreateWindow时有效
		//ModifyStyle(0, BS_OWNERDRAW); //设置BS_OWNERDRAW样式
		return CWindowImpl<CXKnowWTLButton, CButton>::SubclassWindow(hWnd) && ModifyStyle(0, BS_OWNERDRAW);
	}
private:
	BOOL m_bOver;
	BOOL m_bTracking;
	BOOL m_bHandCursor;
};