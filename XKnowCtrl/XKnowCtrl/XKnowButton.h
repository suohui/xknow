#pragma once

//˵�������������ťͼƬֻ�ܺ��Ų��ŷ�һ�𣬲���֧�ֵ�������

///��Ҫ�ڸ����ڵ���Ϣӳ����м���һ��REFLECT_NOTIFICATIONS()�꣬�����ھ��ܹ���֧����Ϣ����Ŀؼ�����������Ϣ������ȥ
///���CHAIN_MSG_MAP_ALT(COwnerDraw<CXKnowButton>, 1)������Ĭ�ϵĻ�����ϢWM_ERASEBKGND��WM_PRINT��WM_PRINTCLIENT�Ͳ��ᴥ��
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
		CRect rcItem = lpDrawItemStruct->rcItem;
		UINT nState = lpDrawItemStruct->itemState;

		CRect rcRectTmp;
		if (nState & ODS_DISABLED)
		{
			rcRectTmp = m_rcDisabled;
		}
		else
		{
			if (m_bOver)
			{
				if (nState & ODS_SELECTED)
				{
					rcRectTmp = m_rcPress;
				}
				else
				{
					rcRectTmp = m_rcHover;
				}
			}
			else
			{
				rcRectTmp = m_rcNormal;
			}
		}
		//˫�����ͼ
		CMemoryDC memDC(hdc, rcItem);
		//������
		CXKnowRender::DrawBkgnd(m_hWnd, memDC, m_hBmpBkgnd, rcItem);
		//��ǰ��
		CXKnowRender::DrawImage(memDC, m_hBmpAllInOne, rcItem, rcRectTmp, m_bAlpha);
		//������
		CXKnowRender::DrawText(memDC, L"��������", rcItem, 0x6D5539, _T("default.font12"), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	CXKnowButton()
	{
		m_hBmpBkgnd = NULL;
		m_bAlpha = FALSE;
		m_bOver = FALSE;
		m_bTracking = FALSE;

		m_bHandCursor = FALSE;

		ZeroMemory(&m_lf, sizeof(m_lf));
		::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(m_lf), &m_lf);
		m_lf.lfCharSet = DEFAULT_CHARSET;
		m_lf.lfHeight = -12;
		m_lf.lfUnderline = TRUE;
		lstrcpy(m_lf.lfFaceName, _T("΢���ź�"));
		m_hFont = ::CreateFontIndirect(&m_lf);
	}
	~CXKnowButton()
	{
		if (m_hBmpAllInOne != NULL)
		{
			DeleteObject(m_hBmpAllInOne);
			m_hBmpAllInOne = NULL;
		}
	}

	void SetHBmpBkgnd(HBITMAP hBmp)
	{
		m_hBmpBkgnd = hBmp;
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

	BOOL SubclassWindow(HWND hWnd)
	{
		//SubclassWindowֻ��CreateWindowʱ��Ч
		//ModifyStyle(0, BS_OWNERDRAW); //����BS_OWNERDRAW��ʽ
		return CWindowImpl<CXKnowButton, CButton>::SubclassWindow(hWnd) && ModifyStyle(0, BS_OWNERDRAW);
	}
private:
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

	HFONT m_hFont;
	LOGFONT m_lf;
};