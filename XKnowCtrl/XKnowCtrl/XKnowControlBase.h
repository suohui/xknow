#pragma once

//������Ϣ������
class CXKnowTextBase
{
public:
	CXKnowTextBase()
	{
		m_strFontID = _T("default.font12");
		m_uFormatStyle = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS;
		m_bMultiLine = FALSE;
		::ZeroMemory(m_dwTextColor, sizeof(m_dwTextColor));
	}

	void SetText(String strText, String strFontID = _T("default.font12"), BOOL bMultiLine = FALSE)
	{
		m_strText = strText;
		m_strFontID = strFontID;
		m_bMultiLine = bMultiLine;
	}

	void SetTextColor(DWORD dwTextNormalColor = 0, DWORD dwTextHoverColor = -1, DWORD dwTextPressColor = -1, DWORD dwTextDisableColor = -1)
	{
		m_dwTextColor[0] = dwTextNormalColor;
		m_dwTextColor[1] = dwTextNormalColor;
		m_dwTextColor[2] = dwTextNormalColor;
		m_dwTextColor[3] = dwTextNormalColor;
		if (dwTextHoverColor != -1)
		{
			m_dwTextColor[1] = dwTextHoverColor;
			m_dwTextColor[2] = dwTextHoverColor;
			m_dwTextColor[3] = dwTextHoverColor;
			if (dwTextPressColor != -1)
			{
				m_dwTextColor[2] = dwTextPressColor;
				m_dwTextColor[3] = dwTextPressColor;
				if (dwTextDisableColor != -1)
				{
					m_dwTextColor[3] = dwTextDisableColor;
				}
			}
		}
	}

	void SetTextRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcText.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}

	void SetTextFormatStyle(UINT uStyle)
	{
		m_uFormatStyle = uStyle;
	}

protected:
	String m_strText;	//��������
	String m_strFontID;	//����ID
	CRect m_rcText;	//���ֻ��ƾ��ο�
	UINT  m_uFormatStyle; //���ֻ�����ʽ
	BOOL m_bMultiLine;	//���С������������Ĭ�ϵĻ�����ʽΪDT_CENTER | DT_VCENTER | DT_SINGLELINE
	DWORD m_dwTextColor[4];//������ɫ
};
//Iconͼ����Ϣ�����࣬��һͼƬ��Ϣ�����磺��ť�ϵı�ʶͼ�ꡢ����LOGO��
class CXKnowIconBase
{
public:
	CXKnowIconBase()
	{
		m_pIconImageInfo = NULL;
	}
	~CXKnowIconBase()
	{
		CXKnowRender::FreeImage(m_pIconImageInfo);
	}

	void SetIconFilePath(String strIconFilePath)
	{
		m_pIconImageInfo = CXKnowRender::LoadImageFromFile(strIconFilePath);
	}

	void SetIconRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcIcon.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}
protected:
	XKnowImageInfo * m_pIconImageInfo;
	CRect m_rcIcon;
};

//ͼƬ��Ϣ�����࣬2-4̬��ͼ��ϣ����磺��ť
class CXKnowImageBase
{
public:
	CXKnowImageBase()
	{
		m_pImageInfo = NULL;
	}
	~CXKnowImageBase()
	{
		CXKnowRender::FreeImage(m_pImageInfo);
	}

	void SetImageFilePath(String strImageFilePath, PNGTYPE type)
	{
		m_pImageInfo = CXKnowRender::LoadImageFromFile(strImageFilePath);
		int iWidth = m_pImageInfo->iWidth;
		int iHeight = m_pImageInfo->iHeight;
		if (type == PNGTYPE::TwoInOne)
		{
			m_rcImageRect[0].SetRect(0, 0, iWidth / 2, iHeight);
			m_rcImageRect[1].SetRect(iWidth / 2, 0, iWidth, iHeight);
			m_rcImageRect[2] = m_rcImageRect[1];
			m_rcImageRect[3] = m_rcImageRect[0];
		}
		else if (type == PNGTYPE::ThreeInOne)
		{
			m_rcImageRect[0].SetRect(0, 0, iWidth / 3, iHeight);
			m_rcImageRect[1].SetRect(iWidth / 3, 0, iWidth * 2 / 3, iHeight);
			m_rcImageRect[2].SetRect(iWidth * 2 / 3, 0, iWidth, iHeight);
			m_rcImageRect[3] = m_rcImageRect[0];
		}
		else if (type == PNGTYPE::FourInOne)
		{
			m_rcImageRect[0].SetRect(0, 0, iWidth / 4, iHeight);
			m_rcImageRect[1].SetRect(iWidth / 4, 0, iWidth * 2 / 4, iHeight);
			m_rcImageRect[2].SetRect(iWidth * 2 / 4, 0, iWidth * 3 / 4, iHeight);
			m_rcImageRect[3].SetRect(iWidth * 3 / 4, 0, iWidth, iHeight);
		}
	}
protected:
	XKnowImageInfo * m_pImageInfo;
	CRect m_rcImageRect[4];
};

template <class T>
class CXKnowControlBase1
{
public:
	CXKnowControlBase1()
	{
		m_hBkgndBmp = NULL;
		
	}
	~CXKnowControlBase1()
	{

	}

	//���ÿؼ�����
	void SetBkgndBitmap(HBITMAP hBmp)
	{
		m_hBkgndBmp = hBmp;
	}

	//���ÿؼ�λ��
	void SetControlPos(int iLeft, int iTop, int iWidth, int iHeight)
	{
		T* pThis = static_cast<T*>(this);
		pThis->MoveWindow(iLeft, iTop, iWidth, iHeight);
	}

protected:
	HBITMAP m_hBkgndBmp;	//�ؼ�����ͼƬ���
};


template <class T>
class CXKnowControlBase : public CMessageMap
{
public:
	CXKnowControlBase()
	{
		m_hBkgndBmp = NULL;
		m_dwBkgndColor = 0;
	}
	~CXKnowControlBase()
	{

	}

	//���ÿؼ�����
	void SetBkgndBitmap(HBITMAP hBmp)
	{
		m_hBkgndBmp = hBmp;
	}

	void SetBkgndColor(DWORD dwColor)
	{
		m_dwBkgndColor = dwColor;
	}

	//���ÿؼ�λ��
	void SetControlPos(int iLeft, int iTop, int iWidth, int iHeight)
	{
		T* pThis = static_cast<T*>(this);
		pThis->MoveWindow(iLeft, iTop, iWidth, iHeight);
	}

	BEGIN_MSG_MAP(CXKnowControlBase)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()
	// Overrideables
	void DoPaint(HDC, CRect)
	{
		// must be implemented
		ATLASSERT(FALSE);
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pThis = static_cast<T*>(this);
		CRect rcClient;
		pThis->GetClientRect(&rcClient);

		CPaintDC dc(pThis->m_hWnd);
		CMemoryDC memDC(dc, rcClient);
		if (0 != m_dwBkgndColor)
			CXKnowRender::DrawColor(memDC, rcClient, m_dwBkgndColor);
		if (NULL != m_hBkgndBmp)
			CXKnowRender::DrawBkgnd(pThis->m_hWnd, memDC, rcClient, m_hBkgndBmp);
		pThis->DoPaint(memDC, rcClient);
		return 0;
	}
protected:
	HBITMAP m_hBkgndBmp;	//�ؼ�����ͼƬ���
	DWORD m_dwBkgndColor;	//�ؼ�������ɫ
};