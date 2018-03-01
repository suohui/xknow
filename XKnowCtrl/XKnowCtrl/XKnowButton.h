#pragma once

//˵�������������ťͼƬֻ�ܺ��Ų��ŷ�һ�𣬲���֧�ֵ�������

///��Ҫ�ڸ����ڵ���Ϣӳ����м���һ��REFLECT_NOTIFICATIONS()�꣬�����ھ��ܹ���֧����Ϣ����Ŀؼ�����������Ϣ������ȥ
///���CHAIN_MSG_MAP_ALT(COwnerDraw<CXKnowButton>, 1)������Ĭ�ϵĻ�����ϢWM_ERASEBKGND��WM_PRINT��WM_PRINTCLIENT�Ͳ��ᴥ��
class CXKnowButton : public CWindowImpl<CXKnowButton, CButton>,
					 public COwnerDraw<CXKnowButton>,
					 public CXKnowTextBase,
					 public CXKnowImageBase,
					 public CXKnowControlBase1<CXKnowButton>			 
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
		//˫�����ͼ
		CMemoryDC memDC(hdc, rcItem);
		//������
		CXKnowRender::DrawBkgnd(m_hWnd, memDC, rcItem, m_hBkgndBmp);
		//��ǰ��
		CXKnowRender::DrawImage(memDC, rcItem, m_pImageInfo->hBitmap, m_rcImageRect[iStateIndex], m_pImageInfo->bAlpha);
		//������
		CXKnowRender::DrawText(memDC, m_strText, m_rcText.IsRectNull() ? rcItem : m_rcText, m_dwTextColor[iStateIndex], m_strFontID, m_uFormatStyle);
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
		//SubclassWindowֻ��CreateWindowʱ��Ч
		//ModifyStyle(0, BS_OWNERDRAW); //����BS_OWNERDRAW��ʽ
		return CWindowImpl<CXKnowButton, CButton>::SubclassWindow(hWnd) && ModifyStyle(0, BS_OWNERDRAW);
	}
private:
	BOOL m_bOver;
	BOOL m_bTracking;
	BOOL m_bHandCursor;
};