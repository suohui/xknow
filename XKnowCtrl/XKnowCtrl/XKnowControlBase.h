#pragma once

//文字信息基础类
class CXKnowTextBase
{
public:
	CXKnowTextBase()
	{
		//设置默认字体ID
		m_strFontID[0] = CXKnowGobal::GetTextNormalFontID();
		m_strFontID[1] = CXKnowGobal::GetTextHoverFontID();
		m_strFontID[2] = CXKnowGobal::GetTextPressFontID();
		m_strFontID[3] = CXKnowGobal::GetTextDisabledFontID();
		//设置默认字体颜色
		m_dwTextColor[0] = CXKnowGobal::GetTextNormalColor();
		m_dwTextColor[1] = CXKnowGobal::GetTextHoverColor();
		m_dwTextColor[2] = CXKnowGobal::GetTextPressColor();
		m_dwTextColor[3] = CXKnowGobal::GetTextDisabledColor();
		//设置默认字体绘制样式
		m_uFormatStyle = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_WORD_ELLIPSIS;
		m_bMultiLine = FALSE;
	}

	void SetText(String strText)
	{
		m_strText = strText;
	}

	void SetTextColor(DWORD dwTextNormalColor, DWORD dwTextHoverColor = -1, DWORD dwTextPressColor = -1, DWORD dwTextDisableColor = -1)
	{
		m_dwTextColor[0] = dwTextNormalColor;
		if (dwTextHoverColor != -1)
		{
			m_dwTextColor[1] = dwTextHoverColor;
			if (dwTextPressColor != -1)
			{
				m_dwTextColor[2] = dwTextPressColor;
				if (dwTextDisableColor != -1)
				{
					m_dwTextColor[3] = dwTextDisableColor;
				}
			}
		}
	}

	void SetTextFontID(String strNormal, String strHover = _T(""), String strPress = _T(""), String strDisable = _T(""))
	{
		m_strFontID[0] = strNormal;
		if (!strHover.empty())
		{
			m_strFontID[1] = strHover;
			if (!strPress.empty())
			{
				m_strFontID[2] = strPress;
				if (!strDisable.empty())
				{
					m_strFontID[3] = strDisable;
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

	void SetTextMultiLine(BOOL bMultiLine)
	{
		m_bMultiLine = bMultiLine;
	}

public:
	String m_strText;	//文字内容
	CRect m_rcText;	//文字绘制矩形框
	UINT  m_uFormatStyle; //文字绘制样式
	BOOL m_bMultiLine;	//多行。简单起见，单行默认的绘制样式为DT_CENTER | DT_VCENTER | DT_SINGLELINE
	DWORD m_dwTextColor[4];//字体颜色
	String m_strFontID[4]; //字体ID
};

















//文字信息基础类
class CXKnowTextInfo
{
public:
	CXKnowTextInfo()
	{
		//设置默认字体ID
		m_arrFontID[0] = CXKnowGobal::GetTextNormalFontID();
		m_arrFontID[1] = CXKnowGobal::GetTextHoverFontID();
		m_arrFontID[2] = CXKnowGobal::GetTextPressFontID();
		m_arrFontID[3] = CXKnowGobal::GetTextDisabledFontID();
		//设置默认字体颜色
		m_arrTextColor[0] = CXKnowGobal::GetTextNormalColor();
		m_arrTextColor[1] = CXKnowGobal::GetTextHoverColor();
		m_arrTextColor[2] = CXKnowGobal::GetTextPressColor();
		m_arrTextColor[3] = CXKnowGobal::GetTextDisabledColor();
		//设置默认字体绘制样式
		m_uFormatStyle = CXKnowGobal::GetTextFormatStyle();
		m_bMultiLine = FALSE;
		m_bVisible = TRUE;
		m_iRowHeight = CXKnowGobal::GetTextRowHeight();
	}

	void SetText(String strText)
	{
		m_strText = strText;
	}

	void SetTextRowHeight(int iHeight)
	{
		m_iRowHeight = iHeight;
	}
	void SetTextVisible(BOOL bVisible)
	{
		m_bVisible = bVisible;
	}

	void SetTextNormalColor(DWORD dwTextNormalColor)
	{
		m_arrTextColor[0] = dwTextNormalColor;
	}

	void SetTextHoverColor(DWORD dwTextHoverColor)
	{
		m_arrTextColor[1] = dwTextHoverColor;
	}

	void SetTextPressColor(DWORD dwTextPressColor)
	{
		m_arrTextColor[2] = dwTextPressColor;
	}

	void SetTextDisabledColor(DWORD dwTextDisabledColor)
	{
		m_arrTextColor[3] = dwTextDisabledColor;
	}

	void SetTextNormalFontID(String strNormalFontID)
	{
		m_arrFontID[0] = strNormalFontID;
	}

	void SetTextHoverFontID(String strHoverFontID)
	{
		m_arrFontID[1] = strHoverFontID;
	}

	void SetTextPressFontID(String strPressFontID)
	{
		m_arrFontID[2] = strPressFontID;
	}

	void SetTextDisabledFontID(String strDisabledFontID)
	{
		m_arrFontID[3] = strDisabledFontID;
	}

	void SetTextRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcText.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
	}

	void SetTextFormatStyle(TEXTFORMAT uStyle)
	{
		m_uFormatStyle = uStyle;
	}

	void SetTextMultiLine(BOOL bMultiLine)
	{
		m_bMultiLine = bMultiLine;
	}

	String GetText()
	{
		return m_strText;
	}

	int GetTextRowHeight()
	{
		return m_iRowHeight;
	}

	BOOL IsTextVisible()
	{
		return m_bVisible;
	}

	DWORD GetTextNormalColor()
	{
		return m_arrTextColor[0];
	}

	DWORD GetTextHoverColor()
	{
		return m_arrTextColor[1];
	}

	DWORD GetTextPressColor()
	{
		return m_arrTextColor[2];
	}

	DWORD GetTextDisabledColor()
	{
		return m_arrTextColor[3];
	}

	String GetTextNormalFontID()
	{
		return m_arrFontID[0];
	}

	String GetTextHoverFontID()
	{
		return m_arrFontID[1];
	}

	String GetTextPressFontID()
	{
		return m_arrFontID[2];
	}

	String GetTextDisabledFontID()
	{
		return m_arrFontID[3];
	}

	CRect GetTextRect()
	{
		return m_rcText;
	}

	TEXTFORMAT GetTextFormatStyle()
	{
		return m_uFormatStyle;
	}

	BOOL IsTextMultiLine()
	{
		return m_bMultiLine;
	}
private:
	String m_arrFontID[4]; //字体ID
	DWORD m_arrTextColor[4];//字体颜色
	TEXTFORMAT  m_uFormatStyle; //文字绘制样式
	BOOL m_bMultiLine;	//多行。简单起见，单行默认的绘制样式为DT_CENTER | DT_VCENTER | DT_SINGLELINE
	BOOL m_bVisible;//是否可见
	int m_iRowHeight;
	String m_strText;	//文字内容
	CRect m_rcText;	//文字绘制矩形框
};

//支持多文本框渲染信息
template <class T>
class CXKnowTextExBase
{
public:
	CXKnowTextExBase()
	{
		m_MultiTextInfoMap.clear();
		
	}
	~CXKnowTextExBase()
	{
		map<String, CXKnowTextInfo*>::iterator iter;
		for (iter = m_MultiTextInfoMap.begin(); iter != m_MultiTextInfoMap.end(); iter++)
		{
			if (NULL != iter->second)
			{
				delete iter->second;
				iter->second = NULL;
			}
		}
		m_MultiTextInfoMap.clear();
	}
	void SetText(String strID, String strText)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetText(strText);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}
	
	void SetTextRowHeight(String strID, int iHeight)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextRowHeight(iHeight);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}
	
	void SetTextVisible(String strID, BOOL bVisible)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextVisible(bVisible);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}
	void SetTextNormalColor(String strID, DWORD dwTextNormalColor)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextNormalColor(dwTextNormalColor);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	void SetTextHoverColor(String strID, DWORD dwTextHoverColor)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextHoverColor(dwTextHoverColor);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	void SetTextPressColor(String strID, DWORD dwTextPressColor)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextPressColor(dwTextPressColor);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	void SetTextDisabledColor(String strID, DWORD dwTextDisabledColor)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextDisabledColor(dwTextDisabledColor);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	void SetTextNormalFontID(String strID, String strNormalFontID)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextNormalFontID(strNormalFontID);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	void SetTextHoverFontID(String strID, String strHoverFontID)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextHoverFontID(strHoverFontID);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	void SetTextPressFontID(String strID, String strPressFontID)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextPressFontID(strPressFontID);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	void SetTextDisabledFontID(String strID, String strDisabledFontID)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextDisabledFontID(strDisabledFontID);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	void SetTextRect(String strID, int iLeft, int iTop, int iWidth, int iHeight)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextRect(iLeft, iTop, iWidth, iHeight);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	void SetTextFormatStyle(String strID, TEXTFORMAT uStyle)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextFormatStyle(uStyle);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	void SetTextMultiLine(String strID, BOOL bMultiLine)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextMultiLine(bMultiLine);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strID), TRUE);
	}

	String GetText(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetText() : _T("");
	}

	int GetTextRowHeight(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextRowHeight() : CXKnowGobal::GetTextRowHeight();
	}

	BOOL IsTextVisible(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->IsTextVisible() : FALSE;
	}

	DWORD GetTextNormalColor(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextNormalColor() : CXKnowGobal::GetTextNormalColor();
	}

	DWORD GetTextHoverColor(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextHoverColor() : CXKnowGobal::GetTextHoverColor();
	}

	DWORD GetTextPressColor(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextPressColor() : CXKnowGobal::GetTextPressColor();
	}

	DWORD GetTextDisabledColor(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextDisabledColor() : CXKnowGobal::GetTextDisabledColor();
	}

	String GetTextNormalFontID(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextNormalFontID() : CXKnowGobal::GetTextNormalFontID();
	}

	String GetTextHoverFontID(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextHoverFontID() : CXKnowGobal::GetTextHoverFontID();
	}

	String GetTextPressFontID(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextPressFontID() : CXKnowGobal::GetTextPressFontID();
	}

	String GetTextDisabledFontID(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextDisabledFontID() : CXKnowGobal::GetTextDisabledFontID();
	}

	CRect GetTextRect(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextRect() : CRect(0, 0, 0, 0);
	}

	UINT GetTextFormatStyle(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetTextFormatStyle() : CXKnowGobal::GetTextFormatStyle();
	}

	BOOL IsTextMultiLine(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->IsTextMultiLine() : FALSE;
	}

	void DrawAllText(HDC hDC)
	{
		map<String, CXKnowTextInfo*>::iterator iter;
		for (iter = m_MultiTextInfoMap.begin(); iter != m_MultiTextInfoMap.end(); iter++)
		{
			CXKnowTextInfo* pTextInfo = iter->second;
			if ((NULL != pTextInfo) && (pTextInfo->IsTextVisible()))
			{
				CXKnowRender::DrawText1(hDC, pTextInfo->GetText(), pTextInfo->GetTextRect(), pTextInfo->GetTextNormalColor(), pTextInfo->GetTextNormalFontID(), pTextInfo->GetTextFormatStyle(), pTextInfo->IsTextMultiLine(), pTextInfo->GetTextRowHeight());




				//CXKnowRender::DrawText(hDC, iter->second->m_strText, iter->second->m_rcText, iter->second->m_dwTextColor[0], iter->second->m_strFontID[0], iter->second->m_uFormatStyle);
			}
		}
	}
private:
	void AddKeyToMap(String strID)
	{
		if (m_MultiTextInfoMap[strID] == NULL)
		{
			m_MultiTextInfoMap[strID] = new CXKnowTextInfo();
		}
	}
	BOOL IsKeyExists(String strID)
	{
		return m_MultiTextInfoMap[strID] != NULL;
	}
private:
	map<String, CXKnowTextInfo*> m_MultiTextInfoMap;
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

	void SetIconRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcIcon.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
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
			m_rcImageRect[0].SetRect(0, 0, iWidth / 2, iHeight);
			m_rcImageRect[1].SetRect(iWidth / 2, 0, iWidth, iHeight);
			m_rcImageRect[2] = m_rcImageRect[1];
			m_rcImageRect[3] = m_rcImageRect[1];
		}
		else if (type == PNGTYPE::ThreeInOne)
		{
			m_rcImageRect[0].SetRect(0, 0, iWidth / 3, iHeight);
			m_rcImageRect[1].SetRect(iWidth / 3, 0, iWidth * 2 / 3, iHeight);
			m_rcImageRect[2].SetRect(iWidth * 2 / 3, 0, iWidth, iHeight);
			m_rcImageRect[3] = m_rcImageRect[2];
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
class CXKnowControlBase
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
public:
	//设置控件背景图片
	void SetBkgndBitmap(HBITMAP hBmp)
	{
		m_hBkgndBmp = hBmp;
		T* pThis = static_cast<T*>(this);
		pThis->InvalidateRect(NULL, FALSE);
	}
	//设置控件背景颜色
	void SetBkgndColor(DWORD dwColor)
	{
		m_dwBkgndColor = dwColor;
		T* pThis = static_cast<T*>(this);
		pThis->InvalidateRect(NULL, FALSE);
	}

protected:
	void DrawControlBkgnd(HDC hdc, CRect rcBkgnd)
	{
		T* pThis = static_cast<T*>(this);
		CDCHandle dc(hdc);
		if (0 != m_dwBkgndColor)
			CXKnowRender::DrawColor(dc, rcBkgnd, m_dwBkgndColor);
		if (NULL != m_hBkgndBmp)
			CXKnowRender::DrawBkgnd(pThis->m_hWnd, dc, rcBkgnd, m_hBkgndBmp);
	}

protected:
	HBITMAP m_hBkgndBmp;	//控件背景图片句柄
	DWORD m_dwBkgndColor;	//控件背景颜色
};