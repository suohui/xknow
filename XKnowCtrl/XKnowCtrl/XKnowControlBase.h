#pragma once

//文字信息基础类
class CXKnowTextBase
{
public:
	CXKnowTextBase()
	{
		m_strFontID = _T("default.font12");
		m_bMultiLine = FALSE;
		m_dwTextNormalColor = 0;
		m_dwTextHoverColor = 0;
		m_dwTextPressColor = 0;
		m_dwTextDisableColor = 0;
	}

	void SetText(String strText, String strFontID = _T("default.font12"), BOOL bMultiLine = FALSE)
	{
		m_strText = strText;
		m_strFontID = strFontID;
		m_bMultiLine = bMultiLine;
	}

	void SetTextColor(DWORD dwTextNormalColor = 0, DWORD dwTextHoverColor = -1, DWORD dwTextPressColor = -1, DWORD dwTextDisableColor = -1)
	{
		m_dwTextNormalColor = dwTextNormalColor;
		m_dwTextHoverColor = dwTextNormalColor;
		m_dwTextPressColor = dwTextNormalColor;
		m_dwTextDisableColor = dwTextNormalColor;
		if (dwTextHoverColor != -1)
		{
			m_dwTextHoverColor = dwTextHoverColor;
			m_dwTextPressColor = dwTextHoverColor;
			m_dwTextDisableColor = dwTextHoverColor;
			if (dwTextPressColor != -1)
			{
				m_dwTextPressColor = dwTextPressColor;
				m_dwTextDisableColor = dwTextPressColor;
				if (dwTextDisableColor != -1)
				{
					m_dwTextDisableColor = dwTextDisableColor;
				}
			}
		}
	}

	void SetTextRect(CRect rcText)
	{
		m_rcText = rcText;
	}
protected:
	String m_strText;	//文字内容
	String m_strFontID;	//字体ID
	CRect m_rcText;	//文字绘制矩形框
	BOOL m_bMultiLine;	//多行。简单起见，单行默认的绘制样式为DT_CENTER | DT_VCENTER | DT_SINGLELINE
	DWORD m_dwTextNormalColor;//字体Normal色
	DWORD m_dwTextHoverColor;//字体Hover色
	DWORD m_dwTextPressColor;//字体Press色
	DWORD m_dwTextDisableColor;//字体Disable色
};
//Icon图标信息基础类，单一图片信息，例如：按钮上的标识图标、窗体LOGO，
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

	void SetIconRect(CRect rcIcon)
	{
		m_rcIcon = rcIcon;
	}
protected:
	XKnowImageInfo * m_pIconImageInfo;
	CRect m_rcIcon;
};

//图片信息基础类，2-4态多图组合，例如：按钮
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
			m_rcImageNormal.SetRect(0, 0, iWidth / 2, iHeight);
			m_rcImageHover.SetRect(iWidth / 2, 0, iWidth, iHeight);
			m_rcImagePress = m_rcImageHover;
			m_rcImageDisabled = m_rcImageNormal;
		}
		else if (type == PNGTYPE::ThreeInOne)
		{
			m_rcImageNormal.SetRect(0, 0, iWidth / 3, iHeight);
			m_rcImageHover.SetRect(iWidth / 3, 0, iWidth * 2 / 3, iHeight);
			m_rcImagePress.SetRect(iWidth * 2 / 3, 0, iWidth, iHeight);
			m_rcImageDisabled = m_rcImageNormal;
		}
		else if (type == PNGTYPE::FourInOne)
		{
			m_rcImageNormal.SetRect(0, 0, iWidth / 4, iHeight);
			m_rcImageHover.SetRect(iWidth / 4, 0, iWidth * 2 / 4, iHeight);
			m_rcImagePress.SetRect(iWidth * 2 / 4, 0, iWidth * 3 / 4, iHeight);
			m_rcImageDisabled.SetRect(iWidth * 3 / 4, 0, iWidth, iHeight);
		}
	}
protected:
	XKnowImageInfo * m_pImageInfo;
	CRect m_rcImageNormal;
	CRect m_rcImageHover;
	CRect m_rcImagePress;
	CRect m_rcImageDisabled;
};

template <class T>
class CXKnowControlBase
{
public:
	CXKnowControlBase()
	{
		m_hBkgndBmp = NULL;
		
	}
	~CXKnowControlBase()
	{

	}

	//设置控件背景
	void SetBkgndBitmap(HBITMAP hBmp)
	{
		m_hBkgndBmp = hBmp;
	}

	//设置控件位置
	void SetControlPos(int iLeft, int iTop, int iWidth, int iHeight)
	{
		T* pThis = static_cast<T*>(this);
		pThis->MoveWindow(iLeft, iTop, iWidth, iHeight);
	}

protected:
	HBITMAP m_hBkgndBmp;	//控件背景图片句柄
};