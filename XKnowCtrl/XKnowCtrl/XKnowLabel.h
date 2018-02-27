#pragma once

class CXKnowLabel : public CWindowImpl<CXKnowLabel, CStatic>
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

		//������
		CXKnowRender::DrawBkgnd(m_hWnd, memDC.m_hDC, m_hBmpBkgnd, rcClient);
		//������
		CXKnowRender::DrawText(memDC.m_hDC, L"�Ҿ��������͵�", rcClient, 0x000000, _T("default.font12"), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		return 0;
	}

	void SetHBmpBkgnd(HBITMAP hBmp)
	{
		m_hBmpBkgnd = hBmp;
	}
private:
	HBITMAP m_hBmpBkgnd;
};
