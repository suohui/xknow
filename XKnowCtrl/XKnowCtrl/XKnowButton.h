#pragma once

//˵�������������ťͼƬֻ�ܺ��Ų��ŷ�һ�𣬲���֧�ֵ�������
//��ȫ����Ϣӳ���˵����https://technet.microsoft.com/zh-cn/hk23896b
//ע����Ϣӳ�� http://blog.sina.com.cn/s/blog_4e0987310101iju5.html
//�������Ҫ�ڸ����ڴ�����Щ��Ϣ������Ҫʹ��CHAIN_MSG_MAP �꽫��Ϣ����ALT_MSG_MAP(1)����
//�������Ҫ�ؼ��Լ�������Щ��Ϣ������Ҫʹ��CHAIN_MSG_MAP_ALT �꽫��Ϣ����ALT_MSG_MAP(1)����
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
		DEFAULT_REFLECTION_HANDLER()	//����Ϣ�������������Խ�����Ӧ
	END_MSG_MAP()

public:
	void DoPaint(HDC hdc, CRect rcClient, int iStateIndex)
	{
		CDCHandle dc(hdc);
		//��ǰ��
		CXKnowRender::DrawImage(dc, rcClient, m_pImageInfo->hBitmap, m_rcImageRect[iStateIndex], m_pImageInfo->bAlpha);
		//������
		CXKnowRender::DrawText(dc, m_strText, m_rcText.IsRectNull() ? rcClient : m_rcText, m_dwTextColor[iStateIndex], m_strFontID[iStateIndex], m_uFormatStyle);
	}
private:
};