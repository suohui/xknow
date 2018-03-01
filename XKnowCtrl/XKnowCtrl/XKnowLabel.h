#pragma once

class CXKnowLabel : public CWindowImpl<CXKnowLabel, CStatic>,
					public CXKnowTextBase,
					public CXKnowControlBase<CXKnowLabel>
{
public:
	CXKnowLabel()
	{

	}
	~CXKnowLabel()
	{

	}

	BEGIN_MSG_MAP(CXKnowLabel)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()
public:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CRect rcClient;
		GetClientRect(&rcClient);

		CPaintDC dc(m_hWnd);
		CMemoryDC memDC(dc, rcClient);
		//»­±³¾°
		CXKnowRender::DrawBkgnd(m_hWnd, memDC, rcClient, m_hBkgndBmp);
		//»­ÎÄ×Ö
		CXKnowRender::DrawText(memDC.m_hDC, m_strText, rcClient, m_dwTextNormalColor, m_strFontID, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS);
		return 0;
	}
};
