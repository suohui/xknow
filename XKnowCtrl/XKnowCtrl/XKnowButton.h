#pragma once


class CDouButton : public CWindowImpl<CDouButton, CButton>,
	public CCustomDraw<CDouButton>,
	public CDouControlBase<CDouButton>,
	public CXKnowTextBase,
	public CXKnowImageBase
{
public:
	CDouButton()
	{
	}
	~CDouButton()
	{
	}

	BEGIN_MSG_MAP(CDouButton)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
		CHAIN_MSG_MAP_ALT(CCustomDraw<CDouButton>, 1)
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
		//����������ǰ����������
		//DrawControlBkgnd(memDC, rcClient);
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










































//˵�������������ťͼƬֻ�ܺ��Ų��ŷ�һ�𣬲���֧�ֵ�������
//��ȫ����Ϣӳ���˵����https://technet.microsoft.com/zh-cn/hk23896b
//ע����Ϣӳ�� http://blog.sina.com.cn/s/blog_4e0987310101iju5.html
//�������Ҫ�ڸ����ڴ�����Щ��Ϣ������Ҫʹ��CHAIN_MSG_MAP �꽫��Ϣ����ALT_MSG_MAP(1)����
//�������Ҫ�ؼ��Լ�������Щ��Ϣ������Ҫʹ��CHAIN_MSG_MAP_ALT �꽫��Ϣ����ALT_MSG_MAP(1)����
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
		//����������ǰ����������
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
