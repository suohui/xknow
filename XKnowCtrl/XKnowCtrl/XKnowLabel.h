#pragma once

class CXKnowLabel : public CWindowImpl<CXKnowLabel, CStatic>,
					public CXKnowControlBase<CXKnowLabel>,
					public CXKnowTextBase
					
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

protected:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		CPaintDC dc(m_hWnd);
		CMemoryDC memDC(dc, rcClient);
		//»­±³¾°¡¢»­ÎÄ×Ö
		DrawControlBkgnd(memDC, rcClient);
		CXKnowRender::DrawText(memDC, m_strText, rcClient, m_dwTextColor[0], m_strFontID[0], m_uFormatStyle, true);
		return 0;
	}
};
