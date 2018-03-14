#pragma once

//文字信息基础类
class CDouTextObject
{
public:
	CDouTextObject(HWND hWndOwner)
	{
		//设置默认字体ID
		m_strFontID = CXKnowGobal::GetTextNormalFontID();
		//设置默认字体颜色
		m_dwTextColor = CXKnowGobal::GetTextNormalColor();
		//设置默认字体绘制样式
		m_uFormatStyle = CXKnowGobal::GetTextFormatStyle();
		m_bMultiLine = FALSE;
		m_bVisible = TRUE;
		m_bHtmlTagEnable = FALSE;
		m_iRowHeight = CXKnowGobal::GetTextRowHeight();
		m_hWndOwner = hWndOwner;
	}

	void SetText(String strText)
	{
		m_strText = strText;
		::InvalidateRect(m_hWndOwner, &m_rcText, TRUE);
	}
	void EnableHtmlTag(BOOL bTagEnable)
	{
		m_bHtmlTagEnable = bTagEnable;
	}
	void SetTextRowHeight(int iHeight)
	{
		m_iRowHeight = iHeight;
	}
	void SetTextVisible(BOOL bVisible)
	{
		m_bVisible = bVisible;
	}

	void SetTextColor(DWORD dwTextColor)
	{
		m_dwTextColor = dwTextColor;
	}

	void SetTextFontID(String strFontID)
	{
		m_strFontID = strFontID;
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

	String GetText()
	{
		return m_strText;
	}

	BOOL IsHtmlTagEnable()
	{
		return m_bHtmlTagEnable;
	}

	int GetTextRowHeight()
	{
		return m_iRowHeight;
	}

	BOOL IsTextVisible()
	{
		return m_bVisible;
	}

	DWORD GetTextColor()
	{
		return m_dwTextColor;
	}

	String GetTextFontID()
	{
		return m_strFontID;
	}

	CRect GetTextRect()
	{
		return m_rcText;
	}

	UINT GetTextFormatStyle()
	{
		return m_uFormatStyle;
	}

	BOOL IsTextMultiLine()
	{
		return m_bMultiLine;
	}
private:
	String m_strFontID; //字体ID
	DWORD m_dwTextColor;//字体颜色
	UINT  m_uFormatStyle; //文字绘制样式
	BOOL m_bMultiLine;	//多行。简单起见，单行默认的绘制样式为DT_CENTER | DT_VCENTER | DT_SINGLELINE
	BOOL m_bVisible;//是否可见
	BOOL m_bHtmlTagEnable;//支持THML标签绘制
	int m_iRowHeight;
	String m_strText;	//文字内容
	CRect m_rcText;	//文字绘制矩形框
	HWND m_hWndOwner;	//控件归属的绘图句柄
};

//Icon图标信息基础类，单一图片信息，例如：按钮上的标识图标、窗体LOGO，
class CDouImageObject
{
public:
	CDouImageObject(HWND hWndOwner)
	{
		m_pImageInfo = NULL;
		m_hWndOwner = hWndOwner;
		m_bVisible = TRUE;
		m_iZOrder = 0;
	}
	~CDouImageObject()
	{
		CXKnowRender::FreeImage(m_pImageInfo);
	}

	void SetImageFilePath(String strFilePath)
	{
		m_pImageInfo = CXKnowRender::LoadImageFromFile(strFilePath);
		::InvalidateRect(m_hWndOwner, &m_rcImage, TRUE);
	}

	void SetImageRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcImage.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
		::InvalidateRect(m_hWndOwner, &m_rcImage, TRUE);
	}

	void SetImageVisible(BOOL bVisible = TRUE)
	{
		m_bVisible = bVisible;
	}

	void SetZOrder(int iZOrder)
	{
		m_iZOrder = iZOrder;
	}

	XKnowImageInfo* GetImageInfo()
	{
		return m_pImageInfo;
	}

	CRect GetImageRect()
	{
		return m_rcImage;
	}

	BOOL IsImageVisible()
	{
		return m_bVisible;
	}

	int GetZOrder()
	{
		return m_iZOrder;
	}
protected:
	XKnowImageInfo * m_pImageInfo;
	HWND m_hWndOwner;	//控件归属的绘图句柄
	BOOL m_bVisible;
	CRect m_rcImage;
	int m_iZOrder;
};

//按钮类
enum DouControlState
{
	Normal,
	Hover,
	LButtonDown,
	LButtonUp
};
class CDouButtonObject
{
public:
	CDouButtonObject(HWND hWndOwner)
	{
		m_pImageInfo = NULL;
		m_hWndOwner = hWndOwner;
		m_bVisible = TRUE;
		m_iLastState = DouControlState::Normal;
		m_iCurState = DouControlState::Normal;
		m_bDown = FALSE;
		m_bHover = FALSE;
	}
	~CDouButtonObject()
	{
		CXKnowRender::FreeImage(m_pImageInfo);
	}
	DouControlState m_iLastState;
	DouControlState m_iCurState;
	BOOL m_bDown;
	BOOL m_bHover;
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


	void SetButtonRect(int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_rcButtonRect.SetRect(iLeft, iTop, iLeft + iWidth, iTop + iHeight);
		::InvalidateRect(m_hWndOwner, &m_rcButtonRect, TRUE);
	}

	void SetButtonVisible(BOOL bVisible = TRUE)
	{
		m_bVisible = bVisible;
	}

	CRect GetButtonRect()
	{
		return m_rcButtonRect;
	}
	BOOL IsButtonVisible()
	{
		return m_bVisible;
	}
public:
	XKnowImageInfo * m_pImageInfo;
	CRect m_rcImageRect[4];
	HWND m_hWndOwner;	//控件归属的绘图句柄
	CRect m_rcButtonRect;
	BOOL m_bVisible;
};






typedef pair<String, int> StringIntPair;
struct CmpByValue
{
	bool operator()(const StringIntPair& left, const StringIntPair& right)
	{
		return left.second < right.second;
	}
};

template <class T>
class CDouControlBase
{
public:
	CDouControlBase()
	{
		m_bTracking = FALSE;
		m_bMouseDown = FALSE;
		m_TextObjectMap.clear();
		m_ImageObjectMap.clear();
		m_ButtonObjectMap.clear();
	}
	~CDouControlBase()
	{
		map<String, CDouTextObject*>::iterator iterText;
		for (iterText = m_TextObjectMap.begin(); iterText != m_TextObjectMap.end(); iterText++)
		{
			if (NULL != iterText->second)
			{
				delete iterText->second;
				iterText->second = NULL;
			}
		}
		m_TextObjectMap.clear();

		map<String, CDouImageObject*>::iterator iterImage;
		for (iterImage = m_ImageObjectMap.begin(); iterImage != m_ImageObjectMap.end(); iterImage++)
		{
			if (NULL != iterImage->second)
			{
				delete iterImage->second;
				iterImage->second = NULL;
			}
		}
		m_ImageObjectMap.clear();

		map<String, CDouButtonObject*>::iterator iterButton;
		for (iterButton = m_ButtonObjectMap.begin(); iterButton != m_ButtonObjectMap.end(); iterButton++)
		{
			if (NULL != iterButton->second)
			{
				delete iterButton->second;
				iterButton->second = NULL;
			}
		}
		m_ButtonObjectMap.clear();
	}
	CDouTextObject* GetTextObject(String strObjID)	//仿FileOpen，如果没有，则创建。如果有，则直接返回
	{
		if (m_TextObjectMap[strObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_TextObjectMap[strObjID] = new CDouTextObject(pThis->m_hWnd);
		}
		return m_TextObjectMap[strObjID];
	}
	CDouImageObject* GetImageObject(String strObjID)
	{
		if (m_ImageObjectMap[strObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ImageObjectMap[strObjID] = new CDouImageObject(pThis->m_hWnd);
		}
		return m_ImageObjectMap[strObjID];
	}

	CDouButtonObject* GetButtonObject(String strObjID)
	{
		if (m_ButtonObjectMap[strObjID] == NULL)
		{
			T* pThis = static_cast<T*>(this);
			m_ButtonObjectMap[strObjID] = new CDouButtonObject(pThis->m_hWnd);
		}
		return m_ButtonObjectMap[strObjID];
	}

	BEGIN_MSG_MAP(CDouControlBase)
		MESSAGE_HANDLER(WM_NCMOUSEMOVE, OnNcMouseMove)
		MESSAGE_HANDLER(WM_NCMOUSELEAVE, OnNcMouseLeave)
		MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnNcLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	END_MSG_MAP()
protected:

	BOOL SetDouControlState(CPoint pt, DouControlState ctlState)
	{
		if (m_bMouseDown)
			return TRUE;
		BOOL bRet = FALSE;
		T* pThis = static_cast<T*>(this);
		//是否落在Button上
		map<String, CDouButtonObject*>::iterator iterButton;
		for (iterButton = m_ButtonObjectMap.begin(); iterButton != m_ButtonObjectMap.end(); iterButton++)
		{
			CDouButtonObject*  pButtonInfo = iterButton->second;	///////////////添加可见与可用的判断
			CRect rcButtonObj = pButtonInfo->GetButtonRect();
			pButtonInfo->m_iLastState = pButtonInfo->m_iCurState;
			if (rcButtonObj.PtInRect(pt))	//落上Button上，绘制
			{
				pButtonInfo->m_iCurState = ctlState;
				if (pButtonInfo->m_iLastState != pButtonInfo->m_iCurState)
					::InvalidateRect(pThis->m_hWnd, &rcButtonObj, TRUE);
				bRet = TRUE;
			}
			else
			{
				if (pButtonInfo->m_iCurState != DouControlState::Normal)
				{
					::InvalidateRect(pThis->m_hWnd, &rcButtonObj, TRUE);
				}
				pButtonInfo->m_iCurState = DouControlState::Normal;
				pButtonInfo->m_iLastState = DouControlState::Normal;
			}
		}
		return bRet;
	}
	
	LRESULT OnNcMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		T* pThis = static_cast<T*>(this);
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		::ScreenToClient(pThis->m_hWnd, &pt);
		SetDouControlState(pt, DouControlState::Hover);

		if (!m_bTracking)
		{
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(TRACKMOUSEEVENT);
			tme.dwFlags = TME_LEAVE | TME_HOVER;
			tme.dwHoverTime = 10;
			tme.hwndTrack = pThis->m_hWnd;
			m_bTracking = ::_TrackMouseEvent(&tme);
		}
		return 0;
	}
	LRESULT OnNcMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		m_bTracking = FALSE;
		SetDouControlState(CPoint(-1, -1), DouControlState::Normal);
		return 0;
	}
	BOOL m_bMouseDown;
	LRESULT OnNcLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pThis = static_cast<T*>(this);
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		::ScreenToClient(pThis->m_hWnd, &pt);
		if (SetDouControlState(pt, DouControlState::LButtonDown))
		{
			m_bMouseDown = TRUE;
			bHandled = TRUE;	//将消息转往客户区
			T* pThis = static_cast<T*>(this);
			::SetCapture(pThis->m_hWnd);
		}
		return 0;
	}
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		ReleaseCapture();
		m_bMouseDown = FALSE;
		T* pThis = static_cast<T*>(this);
		CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		::ScreenToClient(pThis->m_hWnd, &pt);
		SetDouControlState(pt, DouControlState::LButtonUp);

		return 0;
	}
	
	void DrawAllObject(HDC hDC)
	{
		//画图片,先将ZOrder递增排序
		map<String, CDouImageObject*>::iterator iterImage;
		vector<StringIntPair> vecZorder;
		for (iterImage = m_ImageObjectMap.begin(); iterImage != m_ImageObjectMap.end(); iterImage++)
		{
			CDouImageObject* pImageObject = iterImage->second;
			if ((NULL != pImageObject) && (pImageObject->IsImageVisible()) && (pImageObject->GetImageInfo() != NULL) && !pImageObject->GetImageRect().IsRectEmpty())
			{
				vecZorder.push_back(make_pair(iterImage->first, pImageObject->GetZOrder()));
			}
		}
		sort(vecZorder.begin(), vecZorder.end(), CmpByValue());
		vector<StringIntPair>::iterator iterZOrder;
		for (iterZOrder = vecZorder.begin(); iterZOrder != vecZorder.end(); iterZOrder++)	//ZOrder大的在上面
		{
			CDouImageObject* pImageObject = m_ImageObjectMap[iterZOrder->first];
			CXKnowRender::DrawImage(hDC, pImageObject->GetImageRect(), pImageObject->GetImageInfo()->hBitmap, CRect(0, 0, pImageObject->GetImageInfo()->iWidth, pImageObject->GetImageInfo()->iHeight), pImageObject->GetImageInfo()->bAlpha, FALSE);
		}
		//画Button
		map<String, CDouButtonObject*>::iterator iterButton;
		for (iterButton = m_ButtonObjectMap.begin(); iterButton != m_ButtonObjectMap.end(); iterButton++)
		{
			CDouButtonObject*  pButtonInfo = iterButton->second;
			CXKnowRender::DrawImage(hDC, pButtonInfo->GetButtonRect(), pButtonInfo->m_pImageInfo->hBitmap, pButtonInfo->m_rcImageRect[pButtonInfo->m_iCurState], true);
		}
		//画文字
		map<String, CDouTextObject*>::iterator iterText;
		for (iterText = m_TextObjectMap.begin(); iterText != m_TextObjectMap.end(); iterText++)
		{
			CDouTextObject* pTextInfo = iterText->second;
			if ((NULL != pTextInfo) && (pTextInfo->IsTextVisible()) && !pTextInfo->GetText().empty() && !pTextInfo->GetTextRect().IsRectEmpty())
			{
				if (pTextInfo->IsHtmlTagEnable())
				{
					CXKnowRender::DrawHtmlText(hDC, pTextInfo->GetText(), pTextInfo->GetTextRect(), pTextInfo->GetTextColor(), pTextInfo->GetTextFontID(), pTextInfo->GetTextFormatStyle(), pTextInfo->IsTextMultiLine(), pTextInfo->GetTextRowHeight());
				}
				else
				{
					CXKnowRender::DrawText1(hDC, pTextInfo->GetText(), pTextInfo->GetTextRect(), pTextInfo->GetTextColor(), pTextInfo->GetTextFontID(), pTextInfo->GetTextFormatStyle(), pTextInfo->IsTextMultiLine(), pTextInfo->GetTextRowHeight());
				}
			}
		}
	}
private:
	BOOL m_bTracking;
	map<String, CDouTextObject*> m_TextObjectMap;
	map<String, CDouImageObject*> m_ImageObjectMap;
	map<String, CDouButtonObject*> m_ButtonObjectMap;
};



































































































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
		m_bHtmlTagEnable = FALSE;
		m_iRowHeight = CXKnowGobal::GetTextRowHeight();
	}

	void SetText(String strText)
	{
		m_strText = strText;
	}
	void EnableHtmlTag(BOOL bTagEnable)
	{
		m_bHtmlTagEnable = bTagEnable;
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

	void SetTextFormatStyle(UINT uStyle)
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

	BOOL IsHtmlTagEnable()
	{
		return m_bHtmlTagEnable;
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

	UINT GetTextFormatStyle()
	{
		return m_uFormatStyle;
	}

	BOOL IsTextMultiLine()
	{
		return m_bMultiLine;
	}

	DWORD GetTextStateColor(int iState)
	{
		switch (iState)
		{
		case 1:
			return GetTextHoverColor();
		case 2:
			return GetTextPressColor();
		case 3:
			return GetTextDisabledColor();
		default:
			return GetTextNormalColor();
		}
	}
	String GetTextStateFontID(int iState)
	{
		switch (iState)
		{
		case 1:
			return GetTextHoverFontID();
		case 2:
			return GetTextPressFontID();
		case 3:
			return GetTextDisabledFontID();
		default:
			return GetTextNormalFontID();
		}
	}
private:
	String m_arrFontID[4]; //字体ID
	DWORD m_arrTextColor[4];//字体颜色
	UINT  m_uFormatStyle; //文字绘制样式
	BOOL m_bMultiLine;	//多行。简单起见，单行默认的绘制样式为DT_CENTER | DT_VCENTER | DT_SINGLELINE
	BOOL m_bVisible;//是否可见
	BOOL m_bHtmlTagEnable;//支持THML标签绘制
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
	void SetText(String strText, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetText(strText);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void EnableHtmlTag(BOOL bTagEnable, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->EnableHtmlTag(bTagEnable);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}
	
	void SetTextRowHeight(int iHeight, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextRowHeight(iHeight);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}
	
	void SetTextVisible(BOOL bVisible, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextVisible(bVisible);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}
	void SetTextNormalColor(DWORD dwTextNormalColor, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextNormalColor(dwTextNormalColor);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void SetTextHoverColor(DWORD dwTextHoverColor, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextHoverColor(dwTextHoverColor);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void SetTextPressColor(DWORD dwTextPressColor, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextPressColor(dwTextPressColor);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void SetTextDisabledColor(DWORD dwTextDisabledColor, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextDisabledColor(dwTextDisabledColor);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void SetTextNormalFontID(String strNormalFontID, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextNormalFontID(strNormalFontID);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void SetTextHoverFontID(String strHoverFontID, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextHoverFontID(strHoverFontID);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void SetTextPressFontID(String strPressFontID, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextPressFontID(strPressFontID);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void SetTextDisabledFontID(String strDisabledFontID, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextDisabledFontID(strDisabledFontID);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void SetTextRect(int iLeft, int iTop, int iWidth, int iHeight, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextRect(iLeft, iTop, iWidth, iHeight);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void SetTextFormatStyle(UINT uStyle, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextFormatStyle(uStyle);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	void SetTextMultiLine(BOOL bMultiLine, String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		AddKeyToMap(strNewID);
		m_MultiTextInfoMap[strNewID]->SetTextMultiLine(bMultiLine);
		T* pThis = static_cast<T *>(this);
		::InvalidateRect(pThis->m_hWnd, GetTextRect(strNewID), TRUE);
	}

	String GetText(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetText() : _T("");
	}

	BOOL IsHtmlTagEnable(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->IsHtmlTagEnable() : FALSE;
	}

	int GetTextRowHeight(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextRowHeight() : CXKnowGobal::GetTextRowHeight();
	}

	BOOL IsTextVisible(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->IsTextVisible() : TRUE;
	}

	DWORD GetTextNormalColor(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextNormalColor() : CXKnowGobal::GetTextNormalColor();
	}

	DWORD GetTextHoverColor(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextHoverColor() : CXKnowGobal::GetTextHoverColor();
	}

	DWORD GetTextPressColor(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextPressColor() : CXKnowGobal::GetTextPressColor();
	}

	DWORD GetTextDisabledColor(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextDisabledColor() : CXKnowGobal::GetTextDisabledColor();
	}

	String GetTextNormalFontID(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextNormalFontID() : CXKnowGobal::GetTextNormalFontID();
	}

	String GetTextHoverFontID(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextHoverFontID() : CXKnowGobal::GetTextHoverFontID();
	}

	String GetTextPressFontID(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextPressFontID() : CXKnowGobal::GetTextPressFontID();
	}

	String GetTextDisabledFontID(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextDisabledFontID() : CXKnowGobal::GetTextDisabledFontID();
	}

	CRect GetTextRect(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextRect() : CRect(0, 0, 0, 0);
	}

	UINT GetTextFormatStyle(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->GetTextFormatStyle() : CXKnowGobal::GetTextFormatStyle();
	}

	BOOL IsTextMultiLine(String strID = _T(""))
	{
		String strNewID = ResetTextID(strID);
		return IsKeyExists(strNewID) ? m_MultiTextInfoMap[strNewID]->IsTextMultiLine() : FALSE;
	}

	void DrawAllText(HDC hDC, int iState = 0)
	{
		map<String, CXKnowTextInfo*>::iterator iter;
		for (iter = m_MultiTextInfoMap.begin(); iter != m_MultiTextInfoMap.end(); iter++)
		{
			CXKnowTextInfo* pTextInfo = iter->second;
			if ((NULL != pTextInfo) && (pTextInfo->IsTextVisible()) && !pTextInfo->GetText().empty() && !pTextInfo->GetTextRect().IsRectEmpty())
			{
				if (pTextInfo->IsHtmlTagEnable())
				{
					CXKnowRender::DrawHtmlText(hDC, pTextInfo->GetText(), pTextInfo->GetTextRect(), pTextInfo->GetTextStateColor(iState), pTextInfo->GetTextStateFontID(iState), pTextInfo->GetTextFormatStyle(), pTextInfo->IsTextMultiLine(), pTextInfo->GetTextRowHeight());
				}
				else
				{
					CXKnowRender::DrawText1(hDC, pTextInfo->GetText(), pTextInfo->GetTextRect(), pTextInfo->GetTextStateColor(iState), pTextInfo->GetTextStateFontID(iState), pTextInfo->GetTextFormatStyle(), pTextInfo->IsTextMultiLine(), pTextInfo->GetTextRowHeight());
				}
			}
		}
	}
private:
	String ResetTextID(String strID)
	{
		return strID.empty() ? _T("ID.Text.Default") : strID;
	}
	void AddKeyToMap(String strID)
	{
		String strNewID = ResetTextID(strID);
		if (m_MultiTextInfoMap[strNewID] == NULL)
		{
			m_MultiTextInfoMap[strNewID] = new CXKnowTextInfo();
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