#pragma once
typedef std::map<LPCTSTR, HFONT> FONTMAP;
class CXKnowFontManager
{
protected:
	CXKnowFontManager()
	{
		struct FontType
		{
			LPCTSTR sID;
			int  iSize;
			BOOL bBold;
			BOOL bUnderLine;
			BOOL bItalic;
		} fts[] = {
			{_T("default.font12"), 12, FALSE, FALSE, FALSE},
			{_T("default.font13"), 13, FALSE, FALSE, FALSE}
		};

		LOGFONT m_lf;
		::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &m_lf);
		m_lf.lfCharSet = DEFAULT_CHARSET;
		lstrcpy(m_lf.lfFaceName, _T("微软雅黑"));

		for (size_t i = 0; i < sizeof(fts) / sizeof(fts[0]); i++)
		{
			m_lf.lfHeight = -fts[i].iSize;
			m_lf.lfWeight = fts[i].bBold ? FW_BOLD : 0;
			m_lf.lfUnderline = fts[i].bUnderLine;
			m_lf.lfItalic = fts[i].bItalic;
			m_hFontMap[fts[i].sID] = ::CreateFontIndirect(&m_lf);
		}
	}

	~CXKnowFontManager()
	{
		FONTMAP::iterator iter;
		for (iter = m_hFontMap.begin(); iter != m_hFontMap.end(); iter++)
		{
			DeleteObject(iter->second);
		}
	}
public:
	HFONT GetFont(LPCTSTR lpFontID)
	{
		return m_hFontMap[lpFontID];
	}
	static CXKnowFontManager* Instance()
	{
		return m_pFontManager;
	}
private:
	static CXKnowFontManager* m_pFontManager;
	
	FONTMAP m_hFontMap;
};

class CXKnowRender
{
public:
	static void DrawBkgnd(HWND hWnd, HDC hDC, HBITMAP hBkgndBmp, const RECT& rc)
	{
		HDC hMemDC = CreateCompatibleDC(hDC);
		HGDIOBJ hOldBmp = SelectObject(hMemDC, hBkgndBmp);
		CRect rcWindow;
		::GetWindowRect(hWnd, &rcWindow);
		::MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)(LPRECT)&rcWindow, 2);	//获得其在父窗体上的坐标
		::BitBlt(hDC, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hMemDC, rcWindow.left, rcWindow.top, SRCCOPY);

		SelectObject(hMemDC, hOldBmp);
		DeleteDC(hMemDC);
	}

	static void DrawImage(HDC hdc, HBITMAP hBmp, const CRect& rcDst, const CRect& rcSrc, BOOL bAlpha)
	{
		HDC hMemDC = CreateCompatibleDC(hdc);
		HGDIOBJ hOldBmp = SelectObject(hMemDC, hBmp);
		if (bAlpha)
		{
			BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
			AlphaBlend(hdc, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), hMemDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), bf);
		}
		else if (rcSrc.Width()==rcDst.Width() && rcSrc.Height() == rcDst.Height())
		{
			::BitBlt(hdc, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), hMemDC, rcSrc.left, rcSrc.top, SRCCOPY);
		}
		else
		{
			::StretchBlt(hdc, rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), hMemDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), SRCCOPY);
		}
		
		SelectObject(hMemDC, hOldBmp);
		DeleteDC(hMemDC);
	}

	static void DrawText(HDC hdc, LPCTSTR lpText, RECT& rc, DWORD dwTextColor, LPCTSTR lpFontID, UINT uStyle)
	{
		if (NULL == lpText) return;
		::SetBkMode(hdc, TRANSPARENT);
		::SetTextColor(hdc, RGB(GetBValue(dwTextColor), GetGValue(dwTextColor), GetRValue(dwTextColor)));
		HGDIOBJ hOldFont = ::SelectObject(hdc, CXKnowFontManager::Instance()->GetFont(lpFontID));
		::DrawText(hdc, lpText, -1, &rc, uStyle);
		::SelectObject(hdc, hOldFont);
	}
};


