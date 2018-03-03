#pragma once
typedef std::map<String, HFONT> FONTMAP;
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
			{_T("default.font"), 12, FALSE, FALSE, FALSE},
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
		DeleteFont();
	}
public:
	HFONT GetFont(String strFontID)
	{
		return m_hFontMap[strFontID];
	}
	void DeleteFont()
	{
		if (!m_hFontMap.empty())
		{
			FONTMAP::iterator iter;
			for (iter = m_hFontMap.begin(); iter != m_hFontMap.end(); iter++)
			{
				DeleteObject(iter->second);
			}
			m_hFontMap.clear();
		}
	}
	static CXKnowFontManager* Instance()
	{
		return m_pFontManager;
	}
private:
	static CXKnowFontManager* m_pFontManager;
	FONTMAP m_hFontMap;
};

class CXKnowGobal
{
public:
	static String GetImageDir() //图片路径，末尾带//
	{
		TCHAR szExePath[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, szExePath, MAX_PATH);
		PathRemoveFileSpec(szExePath);
		TCHAR szImagePath[MAX_PATH] = { 0 };
		PathCombine(szImagePath, szExePath, _T("..\\img\\"));
		return szImagePath;
	}
	static String GetNormalFontID()	//获取Normal字体
	{
		return _T("default.font");
	}
	static String GetHoverFontID()	//获取Hover字体
	{
		return _T("default.font");
	}
	static String GetPressFontID()	//获取Press字体
	{
		return _T("default.font");
	}
	static String GetDisabledFontID()	//获取Disabled字体
	{
		return _T("default.font");
	}
	static DWORD GetNormalTextColor()	//获取文字Normal色
	{
		return 0;
	}
	static DWORD GetHoverTextColor()	//获取文字Hover色
	{
		return 0;
	}
	static DWORD GetPressTextColor()	//获取文字Press色
	{
		return 0;
	}
	static DWORD GetDisabledTextColor()	//获取文字Disabled色
	{
		return 0;
	}
};

enum PNGTYPE
{
	TwoInOne,
	ThreeInOne,
	FourInOne
};

struct XKnowImageInfo
{
	HBITMAP hBitmap;
	int iWidth;
	int iHeight;
	BOOL bAlpha;
};
class CXKnowRender
{
public:
	static XKnowImageInfo * LoadImageFromFile(String strFileName)
	{
		HANDLE hFile = ::CreateFile(strFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			return NULL;
		}
		DWORD dwSize = ::GetFileSize(hFile, NULL);
		if (dwSize == 0)
		{
			return NULL;
		}
		LPBYTE pData = new BYTE[dwSize];
		DWORD dwRead = 0;
		::ReadFile(hFile, pData, dwSize, &dwRead, NULL);
		::CloseHandle(hFile);
		if (dwRead != dwSize)
		{
			delete[] pData;
			pData = NULL;
			return NULL;
		}
		int x = 1, y = 1, n;
		LPBYTE pImage = stbi_load_from_memory(pData, dwSize, &x, &y, &n, 4);
		delete[] pData;
		pData = NULL;
		if (pImage == NULL)
		{
			return NULL;
		}

		BITMAPINFO bmi;
		::ZeroMemory(&bmi, sizeof(BITMAPINFO));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
		bmi.bmiHeader.biWidth = x;
		bmi.bmiHeader.biHeight = -y;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = x * y * 4;

		BOOL bAlpha = false;
		LPBYTE pDest = NULL;
		HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pDest, NULL, 0);
		if (hBitmap == NULL)
		{
			stbi_image_free(pImage);
			return NULL;
		}

		for (int i = 0; i < x * y; i++)
		{
			pDest[i * 4 + 3] = pImage[i * 4 + 3];
			if (pDest[i * 4 + 3] < 255)
			{
				pDest[i * 4] = (BYTE)(DWORD(pImage[i * 4 + 2])*pImage[i * 4 + 3] / 255);
				pDest[i * 4 + 1] = (BYTE)(DWORD(pImage[i * 4 + 1])*pImage[i * 4 + 3] / 255);
				pDest[i * 4 + 2] = (BYTE)(DWORD(pImage[i * 4])*pImage[i * 4 + 3] / 255);
				bAlpha = TRUE;
			}
			else
			{
				pDest[i * 4] = pImage[i * 4 + 2];
				pDest[i * 4 + 1] = pImage[i * 4 + 1];
				pDest[i * 4 + 2] = pImage[i * 4];
			}
		}
		stbi_image_free(pImage);

		XKnowImageInfo* pImageInfo = new XKnowImageInfo();
		pImageInfo->hBitmap = hBitmap;
		pImageInfo->iWidth = x;
		pImageInfo->iHeight = y;
		pImageInfo->bAlpha = bAlpha;
		return pImageInfo;
	}

	static void FreeImage(XKnowImageInfo* pImageInfo)
	{
		if (NULL != pImageInfo)
		{
			if (NULL != pImageInfo->hBitmap)
			{
				::DeleteObject(pImageInfo->hBitmap);
				pImageInfo->hBitmap = NULL;
			}
			delete pImageInfo;
			pImageInfo = NULL;
		}
	}

	static void DrawBkgnd(HWND hWnd, HDC hDC, const RECT& rc, HBITMAP hBkgndBmp)
	{
		CRect rcWindow;
		::GetWindowRect(hWnd, &rcWindow);
		::MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)(LPRECT)&rcWindow, 2);	//获得其在父窗体上的坐标

		CDCHandle dc(hDC);
		CDC memDC;
		memDC.CreateCompatibleDC(dc);
		HBITMAP hOldBmp = memDC.SelectBitmap(hBkgndBmp);
		dc.BitBlt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, memDC, rcWindow.left, rcWindow.top, SRCCOPY);
		memDC.SelectBitmap(hOldBmp);
	}

	static void DrawImage(HDC hdc, const CRect& rcDst, HBITMAP hBmp, const CRect& rcSrc, BOOL bAlpha, BOOL bStretch = FALSE)
	{
		CDCHandle dc(hdc);
		CDC memDC;
		memDC.CreateCompatibleDC(dc);
		HBITMAP hOldBmp = memDC.SelectBitmap(hBmp);

		int iMinWidth = min(rcDst.Width(), rcSrc.Width());
		int iMinHeight = min(rcDst.Height(), rcSrc.Height());
		if (bAlpha)
		{
			BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
			if (bStretch)
			{
				dc.AlphaBlend(rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), memDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), bf);
			}
			else
			{
				dc.AlphaBlend(rcDst.left, rcDst.top, iMinWidth, iMinHeight, memDC, rcSrc.left, rcSrc.top, iMinWidth, iMinHeight, bf);
			}
		}
		else
		{
			if ((rcSrc.Size() == rcDst.Size()) || !bStretch)
			{
				dc.BitBlt(rcDst.left, rcDst.top, iMinWidth, iMinHeight, memDC, rcSrc.left, rcSrc.top, SRCCOPY);
			}
			else
			{
				dc.StretchBlt(rcDst.left, rcDst.top, rcDst.Width(), rcDst.Height(), memDC, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), SRCCOPY);
			}
		}
		memDC.SelectBitmap(hOldBmp);
	}

	static void DrawColor(HDC hdc, CRect &rcPaint, DWORD dwColor)
	{
		CDCHandle dc(hdc);
		dc.SetBkColor(RGB(GetBValue(dwColor), GetGValue(dwColor), GetRValue(dwColor)));
		dc.ExtTextOut(0, 0, ETO_OPAQUE, &rcPaint, NULL, 0, NULL);
	}

	static void DrawText(HDC hdc, String strText, RECT& rcText, DWORD dwTextColor, String strFontID, UINT uStyle, BOOL bMultipLine = FALSE)
	{
		if (strText.empty()) return;
		CDCHandle dc(hdc);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(GetBValue(dwTextColor), GetGValue(dwTextColor), GetRValue(dwTextColor)));
		HFONT hOldFont = dc.SelectFont(CXKnowFontManager::Instance()->GetFont(strFontID));
		if (bMultipLine)
		{
			int iLength = strText.length();
			int iIndex = 0;
			LPCTSTR lpTmp = strText.c_str();
			int iTop = 0;

			int iRowHeight = 20;
			int iLines = (rcText.bottom - rcText.top) / iRowHeight;
			for (int i = 0; i < iLines; i++)
			{
				//按行来画
				int iStart = 0;
				int iLenTmp = 0;
				SIZE size = { 0, 0 };
				while (size.cx < rcText.right - rcText.left && iIndex + iLenTmp < iLength)
				{
					iStart++;
					iLenTmp++;
					::GetTextExtentPoint32(hdc, lpTmp, iStart, &size);
				}
				if (size.cx > rcText.right - rcText.left)
				{
					iStart--;
				}
				dc.TextOut(0, iTop, lpTmp, iStart);
				iIndex += iStart;
				iTop += iRowHeight;
				lpTmp = strText.c_str() + iIndex;
				if (iIndex < iLength && i == iLines-2) //最后一行特殊处理,超出的 就不再画了
				{
					dc.DrawText(lpTmp, -1, CRect(0, iTop, rcText.right, rcText.bottom), DT_LEFT | DT_WORD_ELLIPSIS);
					break;
				}
			}
		}
		else
		{
			dc.DrawText(strText.c_str(), -1, &rcText, uStyle);
		}
		dc.SelectFont(hOldFont);
	}
};


