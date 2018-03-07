#pragma once

//֧�ֶ�Label
class CXKnowLabelEx : public CWindowImpl<CXKnowLabelEx, CStatic>,
	public CXKnowControlBase<CXKnowLabelEx>,
	public CXKnowTextExBase<CXKnowLabelEx>
{
public:
	CXKnowLabelEx()
	{
	}
	~CXKnowLabelEx()
	{
	}

	BEGIN_MSG_MAP(CXKnowLabelEx)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

protected:
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		CPaintDC dc(m_hWnd);
		CMemoryDC memDC(dc, rcClient);
		//��������������
		DrawControlBkgnd(memDC, rcClient);
		DrawAllText(memDC);
		return 0;
	}
};
