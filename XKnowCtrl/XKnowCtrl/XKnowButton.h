#pragma once

//说明：简单起见，按钮图片只能横着并排放一起，不再支持单独加载

///需要在父窗口的消息映射表中加入一条REFLECT_NOTIFICATIONS()宏，父窗口就能够将支持消息反射的控件所发出的消息反传回去
///添加CHAIN_MSG_MAP_ALT(COwnerDraw<CXKnowButton>, 1)，窗口默认的绘制消息WM_ERASEBKGND、WM_PRINT、WM_PRINTCLIENT就不会触发
class CXKnowButton : public CWindowImpl<CXKnowButton, CButton>,
					 public COwnerDraw<CXKnowButton>,
					 public CXKnowTextBase,
					 public CXKnowImageBase,
					 public CXKnowControlBase<CXKnowButton>			 
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
		CRect rcItem = lpDrawItemStruct->rcItem;
		UINT nState = lpDrawItemStruct->itemState;

		CRect rcRectTmp = m_rcImageNormal;
		DWORD dwTextColor = m_dwTextNormalColor;
		if (nState & ODS_DISABLED)
		{
			rcRectTmp = m_rcImageDisabled;
			dwTextColor = m_dwTextDisableColor;
		}
		else
		{
			if (m_bOver)
			{
				if (nState & ODS_SELECTED)
				{
					rcRectTmp = m_rcImagePress;
					dwTextColor = m_dwTextPressColor;
				}
				else
				{
					rcRectTmp = m_rcImageHover;
					dwTextColor = m_dwTextHoverColor;
				}
			}
		}
		//双缓冲绘图
		CMemoryDC memDC(hdc, rcItem);
		//画背景
		CXKnowRender::DrawBkgnd(m_hWnd, memDC, rcItem, m_hBkgndBmp);
		//画前景
		CXKnowRender::DrawImage(memDC, rcItem, m_pImageInfo->hBitmap, rcRectTmp, m_pImageInfo->bAlpha);
		//画文字
		CXKnowRender::DrawText(memDC, m_strText, m_rcText.IsRectNull() ? rcItem : m_rcText, dwTextColor, m_strFontID, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	CXKnowButton()
	{
		m_bOver = FALSE;
		m_bTracking = FALSE;
		m_bHandCursor = FALSE;
	}
	~CXKnowButton()
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
		return CWindowImpl<CXKnowButton, CButton>::SubclassWindow(hWnd) && ModifyStyle(0, BS_OWNERDRAW);
	}
private:
	BOOL m_bOver;
	BOOL m_bTracking;
	BOOL m_bHandCursor;
};