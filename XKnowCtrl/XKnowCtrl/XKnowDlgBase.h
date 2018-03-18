#pragma once

//Ĭ���ޱ߿򡢿��϶����б�����Icon������
template <class T>
class CXKnowDlgBase : public CMessageMap,
					  public CXKnowTextBase,
					  public CXKnowIconBase,
					  public CDouControlBase<T>
{
public:
	CXKnowDlgBase()
	{
		m_pBkgndImageInfo = NULL;
		m_dwBkgndColor = 0;
	}
	~CXKnowDlgBase()
	{
		CXKnowRender::FreeImage(m_pBkgndImageInfo);
		CXKnowFontManager::Instance()->DeleteFont();
	}

	BEGIN_MSG_MAP(CXKnowDlgBase)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
		CHAIN_MSG_MAP(CDouControlBase)
	END_MSG_MAP()
public:
	// Overrideables//����̳У�����ĳ�ʼ������
	void InitDialog()
	{
		// must be implemented
		ATLASSERT(FALSE);
	}
	//���ñ���ͼƬ·��
	void SetBkgndFilePath(String strFilePath)
	{
		m_pBkgndImageInfo = CXKnowRender::LoadImageFromFile(strFilePath);
	}
	//���ñ�����ɫ
	void SetBkgndColor(DWORD dwColor)
	{
		m_dwBkgndColor = dwColor;
	}
	//��ȡ����ͼƬ���
	HBITMAP GetBkgndHBitmap()
	{
		if (m_pBkgndImageInfo == NULL)
			return NULL;
		else
			return m_pBkgndImageInfo->hBitmap;
	}
	//��ȡ������ɫ
	DWORD GetBkgndColor()
	{
		return m_dwBkgndColor;
	}
protected:
	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pThis = static_cast<T*>(this);
		pThis->SetMsgHandled(TRUE);

		//�޸Ĵ�������
		pThis->SetWindowLong(GWL_STYLE, pThis->GetWindowLong(GWL_STYLE) & (~WS_BORDER) & WS_POPUP);//�ޱ߿���
		pThis->SetWindowLong(GWL_EXSTYLE, pThis->GetWindowLong(GWL_EXSTYLE) | WS_EX_APPWINDOW);    //��ʾ��������
		//����ĳ�ʼ�����������಻����ӦWM_INITDIALOG��ֻ����дInitDialog()�����Ϳ�����
		pThis->InitDialog();

		bHandled = pThis->IsMsgHandled();
		return (LRESULT)TRUE;
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pThis = static_cast<T*>(this);
		CPaintDC dcPaint(pThis->m_hWnd);
		CRect rcClient;
		pThis->GetClientRect(&rcClient);
		
		CMemoryDC dcMem(dcPaint, rcClient);
		//������
		if (m_dwBkgndColor != 0)
			CXKnowRender::DrawColor(dcMem, rcClient, m_dwBkgndColor);
		//if (m_pBkgndImageInfo != NULL)
			CXKnowRender::DrawImage(dcMem, rcClient, CDouBitmapManager::GetInstance()->GetHBitmap(L"MainWnd.bkg"), CDouBitmapManager::GetInstance()->GetBitmapRect(L"MainWnd.bkg"), FALSE, FALSE);
		//��LOGO
		//if (m_pIconImageInfo != NULL && !m_rcIcon.IsRectNull())
		{
			//CXKnowRender::DrawImage(dcMem, m_rcIcon, m_pIconImageInfo->hBitmap, CRect(0, 0, m_pIconImageInfo->iWidth, m_pIconImageInfo->iHeight), m_pIconImageInfo->bAlpha, FALSE);
		}
		//��Title
		DrawAllObject(dcMem);
		//CXKnowRender::DrawText(dcMem, m_strText, m_rcText, m_dwTextColor[0], m_strFontID[0], m_uFormatStyle);

		return 0;
	}
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		return TRUE;
	}

	//�ޱ߿�����϶�https://www.cnblogs.com/findumars/p/5312594.html
	LRESULT OnNcHitTest(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		return HTCAPTION;
	}
private:
	//����
	XKnowImageInfo* m_pBkgndImageInfo;
	DWORD m_dwBkgndColor;
};
