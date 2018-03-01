#pragma once

//说明：简单起见，按钮图片只能横着并排放一起，不再支持单独加载
//注意消息反射 http://blog.sina.com.cn/s/blog_4e0987310101iju5.html
//如果你想要在父窗口处理这些消息，你需要使用CHAIN_MSG_MAP 宏将消息链入ALT_MSG_MAP(1)部分
//如果你想要控件自己处理这些消息，你需要使用CHAIN_MSG_MAP_ALT 宏将消息链入ALT_MSG_MAP(1)部分
class CXKnowButton : public CWindowImpl<CXKnowButton, CButton>,
	public CXKnowTextBase,
	public CXKnowImageBase,
	public CXKnowControlBase<CXKnowButton>
{
public:
	CXKnowButton()
	{
	}
	~CXKnowButton()
	{
	}

	BEGIN_MSG_MAP(CXKnowButton)
		CHAIN_MSG_MAP(CXKnowControlBase)
	END_MSG_MAP()

public:
	void DoPaint(HDC hdc, CRect rcClient, int iStateIndex)
	{
		CDCHandle dc(hdc);
		//画前景
		CXKnowRender::DrawImage(dc, rcClient, m_pImageInfo->hBitmap, m_rcImageRect[iStateIndex], m_pImageInfo->bAlpha);
		//画文字
		CXKnowRender::DrawText(dc, m_strText, m_rcText.IsRectNull() ? rcClient : m_rcText, m_dwTextColor[iStateIndex], m_strFontID[iStateIndex], m_uFormatStyle);
	}
private:
};