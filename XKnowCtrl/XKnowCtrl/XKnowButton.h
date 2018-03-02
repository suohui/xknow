#pragma once

//说明：简单起见，按钮图片只能横着并排放一起，不再支持单独加载
//最全的消息映射宏说明：https://technet.microsoft.com/zh-cn/hk23896b
//注意消息映射 http://blog.sina.com.cn/s/blog_4e0987310101iju5.html
//如果你想要在父窗口处理这些消息，你需要使用CHAIN_MSG_MAP 宏将消息链入ALT_MSG_MAP(1)部分
//如果你想要控件自己处理这些消息，你需要使用CHAIN_MSG_MAP_ALT 宏将消息链入ALT_MSG_MAP(1)部分
class CXKnowButton : public CWindowImpl<CXKnowButton, CButton>,
	public CCustomDraw<CXKnowButton>,
	public CXKnowControlBase<CXKnowButton>,
	public CXKnowTextBase,
	public CXKnowImageBase
{
public:
	CXKnowButton()
	{
	}
	~CXKnowButton()
	{
	}

	BEGIN_MSG_MAP(CXKnowButton)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		CHAIN_MSG_MAP_ALT(CCustomDraw<CXKnowButton>, 1)
	END_MSG_MAP()

public:
	DWORD OnPreErase(int /*uCtrl*/, LPNMCUSTOMDRAW lpNMCD)
	{
		CDCHandle dc(lpNMCD->hdc);
		CRect rcClient = lpNMCD->rc;
		CMemoryDC memDC(dc, rcClient);

		UINT uItemState = lpNMCD->uItemState;
		int iStateIndex = 0;
		if ((lpNMCD->uItemState & CDIS_SELECTED) != 0)
		{
			iStateIndex = 2;
		}
		else if ((lpNMCD->uItemState & CDIS_HOT) != 0)
		{
			iStateIndex = 1;
		}
		else if ((lpNMCD->uItemState & CDIS_DISABLED) != 0)
		{
			iStateIndex = 3;
		}
		//画背景、画前景、画文字
		DrawControlBkgnd(memDC, rcClient);
		CXKnowRender::DrawImage(memDC, rcClient, m_pImageInfo->hBitmap, m_rcImageRect[iStateIndex], m_pImageInfo->bAlpha);
		CXKnowRender::DrawText(memDC, m_strText, m_rcText.IsRectNull() ? rcClient : m_rcText, m_dwTextColor[iStateIndex], m_strFontID[iStateIndex], m_uFormatStyle);
		return CDRF_SKIPDEFAULT;
	}

	LRESULT OnSetCursor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		::SetCursor(::LoadCursor(NULL, IDC_HAND));
		return TRUE;
	}
private:
};
