#pragma once

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
			{_T("default.font13"), 15, FALSE, FALSE, FALSE}
		};

		LOGFONT m_lf;
		::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &m_lf);
		m_lf.lfCharSet = DEFAULT_CHARSET;
		lstrcpy(m_lf.lfFaceName, _T("΢���ź�"));

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
	static String GetImageDir() //ͼƬ·����ĩβ��//
	{
		TCHAR szExePath[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, szExePath, MAX_PATH);
		PathRemoveFileSpec(szExePath);
		TCHAR szImagePath[MAX_PATH] = { 0 };
		PathCombine(szImagePath, szExePath, _T("..\\img\\"));
		return szImagePath;
	}
	static String GetTextNormalFontID()	//��ȡNormal����
	{
		return _T("default.font");
	}
	static String GetTextHoverFontID()	//��ȡHover����
	{
		return _T("default.font");
	}
	static String GetTextPressFontID()	//��ȡPress����
	{
		return _T("default.font");
	}
	static String GetTextDisabledFontID()	//��ȡDisabled����
	{
		return _T("default.font");
	}
	static DWORD GetTextNormalColor()	//��ȡ����Normalɫ
	{
		return 0;
	}
	static DWORD GetTextHoverColor()	//��ȡ����Hoverɫ
	{
		return 0;
	}
	static DWORD GetTextPressColor()	//��ȡ����Pressɫ
	{
		return 0;
	}
	static DWORD GetTextDisabledColor()	//��ȡ����Disabledɫ
	{
		return 0;
	}
	static UINT GetTextFormatStyle()	//��ȡ�ı�������ʽ
	{
		return DT_LEFT | DT_TOP;
	}
	static int GetTextRowHeight()	//��ȡ�����ı����и�
	{
		return 12;
	}
};

struct TextInfo
{
	String strText;
	String strFontID;
	DWORD dwColor;
	int iWidth;
	int iHeight;
};

#ifdef _UNICODE
#define ZIPENTRY ZIPENTRYW
#endif

class CXKnowRender
{
public:
	static XKnowImageInfo * LoadImageFromFile(String strFileName, int itype = 0)
	{
		LPBYTE pData = NULL;
		DWORD dwSize = 0;
		if (itype == 0)
		{
			HANDLE hFile = ::CreateFile(strFileName.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE)
			{
				return NULL;
			}
			dwSize = ::GetFileSize(hFile, NULL);
			if (dwSize == 0)
			{
				return NULL;
			}
			pData = new BYTE[dwSize];
			DWORD dwRead = 0;
			::ReadFile(hFile, pData, dwSize, &dwRead, NULL);
			::CloseHandle(hFile);
			if (dwRead != dwSize)
			{
				delete[] pData;
				pData = NULL;
				return NULL;
			}
		}
		else
		{
			HZIP hz = OpenZip((void *)L"C:\\Users\\Suo\\Desktop\\����.zip", 0, 2);	//ZIP_FILENAME
			if (hz == NULL)
			{
				return NULL;
			}
			ZIPENTRY ze;
			int i;
			FindZipItem(hz, L"����\\FLOAT.png", true, &i, &ze);
			dwSize = ze.unc_size;
			if (dwSize == 0)
			{
				return NULL;
			}
			pData = new BYTE[dwSize];
			int iRet = UnzipItem(hz, i, pData, dwSize, 3);
			if (iRet != 0x00000000 && iRet != 0x00000600)
			{
				delete[] pData;
				pData = NULL;
				CloseZip(hz);
				return NULL;
			}
			CloseZip(hz);
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
		::MapWindowPoints(NULL, GetParent(hWnd), (LPPOINT)(LPRECT)&rcWindow, 2);	//������ڸ������ϵ�����

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
	//������ɫ
	static void DrawColor(HDC hdc, CRect &rcPaint, DWORD dwColor)
	{
		CDCHandle dc(hdc);
		dc.SetBkColor(RGB(GetBValue(dwColor), GetGValue(dwColor), GetRValue(dwColor)));
		dc.ExtTextOut(0, 0, ETO_OPAQUE, &rcPaint, NULL, 0, NULL);
	}
	//���Ƶ����ı�
	static void DrawSingleLineText(HDC hdc, String strText, RECT rcText, DWORD dwTextColor, String strFontID, UINT uFormat)
	{
		CDCHandle dc(hdc);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(GetBValue(dwTextColor), GetGValue(dwTextColor), GetRValue(dwTextColor)));
		HFONT hOldFont = dc.SelectFont(CXKnowFontManager::Instance()->GetFont(strFontID));
		SIZE szText = { 0, 0 };
		::GetTextExtentPoint32(dc, strText.c_str(), strText.length(), &szText);
		String strPaint = _T("");
		CRect rcTextClient = rcText;
		if (szText.cx > rcTextClient.Width())	//����̫�࣬���Ʋ��꣬��...����
		{
			String strEndEllipsis = _T("...");
			SIZE szEndEllipsis = { 0, 0 };
			::GetTextExtentPoint32(dc, strEndEllipsis.c_str(), strEndEllipsis.length(), &szEndEllipsis);
			if (szEndEllipsis.cx < rcTextClient.Width()) //���...Ҳ�����ˣ�˵�����̫С��
			{
				int iStart = 0;
				szText = { 0, 0 };
				while (szText.cx < rcTextClient.Width() - szEndEllipsis.cx)
				{
					iStart++;
					::GetTextExtentPoint32(dc, strText.c_str(), iStart, &szText);
				}
				if (szText.cx > rcTextClient.Width() - szEndEllipsis.cx)
				{
					iStart--;
				}
				strPaint = strText.substr(0, iStart) + strEndEllipsis;
			}
		}
		else
			strPaint = strText;

		CPoint ptPaintPoint = GetTextPaintPoint(rcTextClient, szText, uFormat);
		dc.TextOut(ptPaintPoint.x, ptPaintPoint.y, strPaint.c_str(), -1);
		dc.SelectFont(hOldFont);
	}
	//�����ı���С�ͻ�����ʽ��ȷ�����Ͻǵ�
	static CPoint GetTextPaintPoint(CRect rcCtrlRect, CSize szText, UINT uFormat)
	{
		CPoint ptLeftTop(rcCtrlRect.left, rcCtrlRect.top);
		if ((uFormat & DT_RIGHT) != 0)
			ptLeftTop.x = rcCtrlRect.left - szText.cx;
		if ((uFormat & DT_BOTTOM) != 0)
			ptLeftTop.y = rcCtrlRect.bottom - szText.cy;
		if ((uFormat & DT_CENTER) != 0)
			ptLeftTop.x = (rcCtrlRect.Width() - szText.cx) / 2;
		if ((uFormat & DT_VCENTER) != 0)
			ptLeftTop.y = (rcCtrlRect.Height() - szText.cy) / 2;
		return ptLeftTop;
	}
	//���Ƶ���HTML�ı�
	//"<html fontid="" color="#">�򵥵Ļ��ƣ���֧��Ƕ��</html>"
	static void DrawHtmlSingleLineText(HDC hdc, String strText, RECT rcText, DWORD dwTextColor, String strFontID, UINT uFormat)
	{
		std::vector<TextInfo*> vecTextInfo;
		vecTextInfo.clear();
		int iTotalWidth = 0;
		int iMaxHeight = 0;
		GetHtmlStringExtend(hdc, strText, dwTextColor, strFontID, vecTextInfo, iTotalWidth, iMaxHeight);	//��HTML�ı���������
		CPoint ptLeftTop = GetTextPaintPoint(rcText, CSize(iTotalWidth, iMaxHeight), uFormat);	//��ȡ���Ƶ����Ͻǵ㣬���ڸ߶Ȳ�һ�£�����ȫ����DT_BOTTOM

		size_t vceLength = vecTextInfo.size();
		int iLeft = ptLeftTop.x;
		int iTop = ptLeftTop.y;
		for (size_t iIndex = 0; iIndex < vceLength; iIndex++)	//��һ����
		{
			TextInfo* pTextInfo = vecTextInfo[iIndex];
			CRect rcText(iLeft, iTop, iLeft + pTextInfo->iWidth, iTop + iMaxHeight);
			DrawSingleLineText(hdc, pTextInfo->strText, rcText, pTextInfo->dwColor, pTextInfo->strFontID, DT_BOTTOM);
			iLeft = iLeft + pTextInfo->iWidth;
		}
	}
	//���ƶ����ı�
	static void DrawMultiLineText(HDC hdc, String strText, RECT rcText, DWORD dwTextColor, String strFontID, int iRowHeight)
	{
		CDCHandle dc(hdc);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(GetBValue(dwTextColor), GetGValue(dwTextColor), GetRValue(dwTextColor)));
		HFONT hOldFont = dc.SelectFont(CXKnowFontManager::Instance()->GetFont(strFontID));
		{
			int iLength = strText.length();
			int iIndex = 0;
			LPCTSTR lpTmp = strText.c_str();
			int iTop = 0;

			int iLines = (rcText.bottom - rcText.top) / iRowHeight;
			for (int i = 0; i < iLines; i++)
			{
				//��������
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
				if (iIndex < iLength && i == iLines - 2) //���һ�����⴦��,������ �Ͳ��ٻ���
				{
					DrawSingleLineText(hdc, lpTmp, CRect(0, iTop, rcText.right, rcText.bottom), dwTextColor, strFontID, DT_LEFT | DT_TOP);
					break;
				}
			}
		}

		dc.SelectFont(hOldFont);
	}

	static void DrawText1(HDC hdc, String strText, RECT& rcText, DWORD dwTextColor, String strFontID, UINT uFormat, BOOL bMultipLine, int iRowHeight)
	{
		if (bMultipLine)
		{
			DrawMultiLineText(hdc, strText, rcText, dwTextColor, strFontID, iRowHeight);
		}
		else
		{
			DrawSingleLineText(hdc, strText, rcText, dwTextColor, strFontID, uFormat);
		}
	}
	//����HTML�ı�
	static void DrawHtmlText(HDC hdc, String strText, RECT& rcText, DWORD dwTextColor, String strFontID, UINT uFormat, BOOL bMultipLine, int iRowHeight)
	{
		if (bMultipLine)
		{
			DrawMultiLineText(hdc, strText, rcText, dwTextColor, strFontID, iRowHeight);
		}
		else
		{
			DrawHtmlSingleLineText(hdc, strText, rcText, dwTextColor, strFontID, uFormat);
		}
	}
	//����
	static void DrawText(HDC hdc, String strText, RECT& rcText, DWORD dwTextColor, String strFontID, UINT uStyle, BOOL bMultipLine = FALSE, int iRowHeight = CXKnowGobal::GetTextRowHeight())
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
				//��������
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
				if (iIndex < iLength && i == iLines-2) //���һ�����⴦��,������ �Ͳ��ٻ���
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
	//��ȡHTML��ǩ��ֵ
	static String GetHtmlTagValue(String strStyleText, String strTag)
	{
		String strRet = _T("");
		size_t iFound = strStyleText.find(strTag);
		if (iFound != String::npos)
		{
			size_t iQuotesLeft = strStyleText.find(_T('\"'), iFound);
			if (iQuotesLeft != String::npos)
			{
				size_t iQuotesRight = strStyleText.find(_T('\"'), iQuotesLeft + 1);
				if (iQuotesRight != String::npos)
				{
					strRet = strStyleText.substr(iQuotesLeft + 1, iQuotesRight - iQuotesLeft - 1);
				}
			}
		}
		return strRet;
	}
	//����TextInfo�ṹ
	static TextInfo* GetTextInfo(HDC hdc, String strText, DWORD dwColor, String strFontID)
	{
		CDCHandle dc(hdc);
		HFONT hOldFont = dc.SelectFont(CXKnowFontManager::Instance()->GetFont(strFontID));
		SIZE szText = { 0, 0 };
		::GetTextExtentPoint32(dc, strText.c_str(), strText.length(), &szText);
		dc.SelectFont(hOldFont);
		TextInfo *pTextInfo = new TextInfo;
		pTextInfo->strText = strText;
		pTextInfo->strFontID = strFontID;
		pTextInfo->dwColor = dwColor;
		pTextInfo->iWidth = szText.cx;
		pTextInfo->iHeight = szText.cy;
		return pTextInfo;
	}
	//��HTML�ļ��ָ�������ȡ�ܿ�� �� ���߶�
	static void GetHtmlStringExtend(HDC hdc, String strText, DWORD dwDefaultColor, String strDefaultFontID, vector<TextInfo *> &vecTextInfoRet, int &iTotalWidth, int &iMaxHeight)
	{
		iTotalWidth = 0;
		iMaxHeight = 0;
		size_t iStart = 0;
		String strTmp = strText;
		do
		{
			size_t nTagStartLeft = strTmp.find(_T("<html"));
			if (nTagStartLeft == String::npos)
			{
				//���������//���һ��
				TextInfo *pNormalTextInfo = GetTextInfo(hdc, strTmp.substr(iStart), dwDefaultColor, strDefaultFontID);
				iTotalWidth += pNormalTextInfo->iWidth;
				iMaxHeight = max(iMaxHeight, pNormalTextInfo->iHeight);
				vecTextInfoRet.push_back(pNormalTextInfo);
				break;
			}
			else
			{
				size_t nTagStartRight = strTmp.find(_T(">"));
				size_t nTagEnd = strTmp.find(_T("</html>"), nTagStartRight);
				if ((nTagStartRight == String::npos) || (nTagEnd == String::npos))
				{
					break;
				}
				//���������
				String strNormalText = strTmp.substr(iStart, nTagStartLeft);
				if (!strNormalText.empty())
				{
					TextInfo *pNormalTextInfo = GetTextInfo(hdc, strNormalText, dwDefaultColor, strDefaultFontID);
					iTotalWidth += pNormalTextInfo->iWidth;
					iMaxHeight = max(iMaxHeight, pNormalTextInfo->iHeight);
					vecTextInfoRet.push_back(pNormalTextInfo);
				}
				//���html���ε�
				String strHtmlText = strTmp.substr(nTagStartRight + 1, nTagEnd - nTagStartRight - 1);
				if (!strHtmlText.empty())
				{
					String strStyle = strTmp.substr(nTagStartLeft + 6, nTagStartRight - nTagStartLeft - 6);
					String strHtmlFontID = GetHtmlTagValue(strStyle, _T("fontid"));
					String strHtmlColor = GetHtmlTagValue(strStyle, _T("color"));
					LPTSTR lpEndPtr;
					DWORD dwColor = strHtmlColor.empty() ? dwDefaultColor : _tcstol(strHtmlColor.c_str()+1, &lpEndPtr, 16);
					String strFont = strHtmlFontID.empty() ? strDefaultFontID : strHtmlFontID;
					TextInfo *pHtmlTextInfo = GetTextInfo(hdc, strHtmlText, dwColor, strFont);
					iTotalWidth += pHtmlTextInfo->iWidth;
					iMaxHeight = max(iMaxHeight, pHtmlTextInfo->iHeight);
					vecTextInfoRet.push_back(pHtmlTextInfo);
					strTmp = strTmp.substr(nTagEnd + 7);
				}
			}
		} while (!strTmp.empty());
	}
};


