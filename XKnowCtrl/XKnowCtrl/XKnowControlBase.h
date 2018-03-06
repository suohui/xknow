#pragma once

//������Ϣ������
class CXKnowTextBase
{
public:
	CXKnowTextBase()
	{
		//����Ĭ������ID
		m_strFontID[0] = CXKnowGobal::GetTextNormalFontID();
		m_strFontID[1] = CXKnowGobal::GetTextHoverFontID();
		m_strFontID[2] = CXKnowGobal::GetTextPressFontID();
		m_strFontID[3] = CXKnowGobal::GetTextDisabledFontID();
		//����Ĭ��������ɫ
		m_dwTextColor[0] = CXKnowGobal::GetTextNormalColor();
		m_dwTextColor[1] = CXKnowGobal::GetTextHoverColor();
		m_dwTextColor[2] = CXKnowGobal::GetTextPressColor();
		m_dwTextColor[3] = CXKnowGobal::GetTextDisabledColor();
		//����Ĭ�����������ʽ
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
	String m_strText;	//��������
	CRect m_rcText;	//���ֻ��ƾ��ο�
	UINT  m_uFormatStyle; //���ֻ�����ʽ
	BOOL m_bMultiLine;	//���С������������Ĭ�ϵĻ�����ʽΪDT_CENTER | DT_VCENTER | DT_SINGLELINE
	DWORD m_dwTextColor[4];//������ɫ
	String m_strFontID[4]; //����ID
};

















//������Ϣ������
class CXKnowTextInfo
{
public:
	CXKnowTextInfo()
	{
		//����Ĭ������ID
		m_arrFontID[0] = CXKnowGobal::GetTextNormalFontID();
		m_arrFontID[1] = CXKnowGobal::GetTextHoverFontID();
		m_arrFontID[2] = CXKnowGobal::GetTextPressFontID();
		m_arrFontID[3] = CXKnowGobal::GetTextDisabledFontID();
		//����Ĭ��������ɫ
		m_arrTextColor[0] = CXKnowGobal::GetTextNormalColor();
		m_arrTextColor[1] = CXKnowGobal::GetTextHoverColor();
		m_arrTextColor[2] = CXKnowGobal::GetTextPressColor();
		m_arrTextColor[3] = CXKnowGobal::GetTextDisabledColor();
		//����Ĭ�����������ʽ
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
private:
	String m_arrFontID[4]; //����ID
	DWORD m_arrTextColor[4];//������ɫ
	UINT  m_uFormatStyle; //���ֻ�����ʽ
	BOOL m_bMultiLine;	//���С������������Ĭ�ϵĻ�����ʽΪDT_CENTER | DT_VCENTER | DT_SINGLELINE
	BOOL m_bVisible;//�Ƿ�ɼ�
	int m_iRowHeight;
	String m_strText;	//��������
	CRect m_rcText;	//���ֻ��ƾ��ο�
};

//֧�ֶ��ı�����Ⱦ��Ϣ
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
	}
	
	void SetRowHeight(String strID, int iHeight)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextRowHeight(iHeight);
	}
	
	void SetTextVisible(String strID, BOOL bVisible)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextVisible(bVisible);
	}
	void SetTextNormalColor(String strID, DWORD dwTextNormalColor)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextNormalColor(dwTextNormalColor);
	}

	void SetTextHoverColor(String strID, DWORD dwTextHoverColor)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextHoverColor(dwTextHoverColor);
	}

	void SetTextPressColor(String strID, DWORD dwTextPressColor)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextPressColor(dwTextPressColor);
	}

	void SetTextDisabledColor(String strID, DWORD dwTextDisabledColor)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextDisabledColor(dwTextDisabledColor);
	}

	void SetTextNormalFontID(String strID, String strNormalFontID)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextNormalFontID(strNormalFontID);
	}

	void SetTextHoverFontID(String strID, String strHoverFontID)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextHoverFontID(strHoverFontID);
	}

	void SetTextPressFontID(String strID, String strPressFontID)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextPressFontID(strPressFontID);
	}

	void SetTextDisabledFontID(String strID, String strDisabledFontID)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextDisabledFontID(strDisabledFontID);
	}

	void SetTextRect(String strID, int iLeft, int iTop, int iWidth, int iHeight)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextRect(iLeft, iTop, iWidth, iHeight);
	}

	void SetTextFormatStyle(String strID, UINT uStyle)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextFormatStyle(uStyle);
	}

	void SetTextMultiLine(String strID, BOOL bMultiLine)
	{
		AddKeyToMap(strID);
		m_MultiTextInfoMap[strID]->SetTextMultiLine(bMultiLine);
	}

	String GetText(String strID)
	{
		return IsKeyExists(strID) ? m_MultiTextInfoMap[strID]->GetText() : _T("");
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















class CXKnowMultiTextBase
{
public:
	CXKnowMultiTextBase()
	{
		m_MultiTextInfoMap.clear();
	}
	~CXKnowMultiTextBase()
	{
		map<String, CXKnowTextBase*>::iterator iter;
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
		m_MultiTextInfoMap[strID]->SetText(strText);
	}

	void SetTextColor(String strID, DWORD dwTextNormalColor)
	{
		m_MultiTextInfoMap[strID]->SetTextColor(dwTextNormalColor);
	}

	void SetTextFontID(String strID, String strNormal)
	{
		m_MultiTextInfoMap[strID]->SetTextFontID(strNormal);
	}

	void SetTextRect(String strID, int iLeft, int iTop, int iWidth, int iHeight)
	{
		m_MultiTextInfoMap[strID]->SetTextRect(iLeft, iTop, iWidth, iHeight);
	}

	void SetTextFormatStyle(String strID, UINT uStyle)
	{
		m_MultiTextInfoMap[strID]->SetTextFormatStyle(uStyle);
	}

	void SetTextMultiLine(String strID, BOOL bMultiLine)
	{
		m_MultiTextInfoMap[strID]->SetTextMultiLine(bMultiLine);
	}

	void DrawTextMap(HDC hDC)
	{
		map<String, CXKnowTextBase*>::iterator iter;
		for (iter = m_MultiTextInfoMap.begin(); iter != m_MultiTextInfoMap.end(); iter++)
		{
			if (NULL != iter->second)
			{
				CXKnowRender::DrawText(hDC, iter->second->m_strText, iter->second->m_rcText, iter->second->m_dwTextColor[0], iter->second->m_strFontID[0], iter->second->m_uFormatStyle);
			}
		}
	}
private:
	map<String, CXKnowTextBase*> m_MultiTextInfoMap;
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
	//���ÿؼ�����ͼƬ
	void SetBkgndBitmap(HBITMAP hBmp)
	{
		m_hBkgndBmp = hBmp;
		T* pThis = static_cast<T*>(this);
		pThis->InvalidateRect(NULL, FALSE);
	}
	//���ÿؼ�������ɫ
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
	HBITMAP m_hBkgndBmp;	//�ؼ�����ͼƬ���
	DWORD m_dwBkgndColor;	//�ؼ�������ɫ
};