#pragma once

class CXKnowLabel : public CWindowImpl<CXKnowLabel, CStatic>,
					public CXKnowTextBase,
					public CXKnowControlBase<CXKnowLabel>
{
public:
	CXKnowLabel()
	{
		//
	}
	~CXKnowLabel()
	{
		//
	}

	BEGIN_MSG_MAP(CXKnowLabel)
		CHAIN_MSG_MAP(CXKnowControlBase)
	END_MSG_MAP()
public:
	void DoPaint(HDC hdc, CRect rcClient, int iStateIndex)
	{
		CXKnowRender::DrawText(hdc, m_strText, rcClient, m_dwTextColor[0], m_strFontID[0], m_uFormatStyle);
	}
};
