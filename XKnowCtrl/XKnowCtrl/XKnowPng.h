#pragma once
#include "stdafx.h"

#define PROGNAME  "VisualPng"
#define LONGNAME  "Win32 Viewer for PNG-files"
#define VERSION   "1.0 of 2000 June 07"

/* constants */

#define MARGIN 8
static char *szProgName = PROGNAME;



class XKnowPngInfo
{
public:
	XKnowPngInfo();
	~XKnowPngInfo();

	BOOL ReadPng(LPCTSTR lpszFileName)
	{
		/* open the PNG input file */
		if (lpszFileName == NULL) { return FALSE; }
		FILE *fp;
		//if (0 != _tfopen_s(&pfFile, lpszFileName, _T("rb"))) { return FALSE; }
		fp = fopen("D:\\1.png", "rb");
		/* first check the eight byte PNG signature */
		//png_byte pbSig[8] = { 0 };
		//fread(pbSig, 1, 8, pfFile);
		//if (png_sig_cmp(pbSig, 0, 8) != 0)
		//{
		//	fclose(pfFile);////////////////////////////////////////////////////////////////////////
		//	return FALSE;
		//}
		/* create the two png(-info) structures */
		png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (png_ptr == NULL) { return FALSE; }
		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL)
		{ 
			png_destroy_read_struct(&png_ptr, NULL, NULL);
			return FALSE;
		}
		/* initialize the png structure */
		png_init_io(png_ptr, fp);
		//png_set_sig_bytes(png_ptr, 8);
		/* read all PNG info up to image data */
		png_read_info(png_ptr, info_ptr);
		/* get width, height, bit-depth and color-type */
		png_get_IHDR(png_ptr, info_ptr, &m_iWidth, &m_iHeight, &m_iBitDepth, &m_iColorType, NULL, NULL, NULL);
		if (m_iColorType == PNG_COLOR_TYPE_PALETTE)
			png_set_palette_to_rgb(png_ptr);//要求转换索引颜色到RGB
		if (m_iColorType == PNG_COLOR_TYPE_GRAY && m_iBitDepth < 8)
			png_set_expand_gray_1_2_4_to_8(png_ptr);//要求位深度强制8bit
		if (m_iBitDepth == 16)
			png_set_strip_16(png_ptr);//要求位深度强制8bit
		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
			png_set_tRNS_to_alpha(png_ptr);
		if (m_iColorType == PNG_COLOR_TYPE_GRAY || m_iColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
			png_set_gray_to_rgb(png_ptr);//灰度必须转换成RGB

		

		COLORREF **ppLinePtrs = NULL;
		ppLinePtrs = (COLORREF **)malloc(m_iHeight * sizeof(COLORREF *));//列指针
		COLORREF *g_pBits = new COLORREF[m_iHeight * m_iWidth];		//位图指针

		int i = m_iHeight;
		int y = 0;
		while (i--)
		{
			ppLinePtrs[y++] = (COLORREF *)&g_pBits[i * m_iWidth];
		}
		png_read_image(png_ptr, (png_bytepp)ppLinePtrs);
		png_read_end(png_ptr, info_ptr);

		BYTE *Bits = NULL;
		Bits = (BYTE*)g_pBits;
		//然后设置好透明混合。
		y = m_iHeight;
		while (y--)
		{
			png_byte r, g, b;
			for (i = 0; i<m_iHeight; i++)
			{
				r = Bits[0];
				g = Bits[1];
				b = Bits[2];
				Bits[0] = b * Bits[3] / 255;
				Bits[1] = g * Bits[3] / 255;
				Bits[2] = r * Bits[3] / 255;
				Bits += 4;
			}
		}


		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);



	}

	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }
private:
	unsigned int m_iWidth;
	unsigned int m_iHeight;
	int m_iBitDepth;
	int m_iColorType;
};

XKnowPngInfo::XKnowPngInfo()
{
	m_iWidth = 0;
	m_iHeight = 0;
}

XKnowPngInfo::~XKnowPngInfo()
{
}







































































BOOL InitBitmap(BYTE *pDiData, int cxWinSize, int cyWinSize)
{
	BYTE *dst;
	int x, y, col;

	/* initialize the background with gray */

	dst = pDiData;
	for (y = 0; y < cyWinSize; y++)
	{
		col = 0;
		for (x = 0; x < cxWinSize; x++)
		{
			/* fill with GRAY */
			*dst++ = 127;
			*dst++ = 127;
			*dst++ = 127;
			col += 3;
		}
		/* rows start on 4 byte boundaries */
		while ((col % 4) != 0)
		{
			dst++;
			col++;
		}
	}

	return TRUE;
}

BOOL FillBitmap(
	BYTE *pDiData, int cxWinSize, int cyWinSize,
	BYTE *pbImage, int cxImgSize, int cyImgSize, int cImgChannels,
	BOOL bStretched)
{
	BYTE *pStretchedImage;
	BYTE *pImg;
	BYTE *src, *dst;
	BYTE r, g, b, a;
	const int cDIChannels = 3;
	WORD wImgRowBytes;
	WORD wDIRowBytes;
	int cxNewSize, cyNewSize;
	int cxImgPos, cyImgPos;
	int xImg, yImg;
	int xWin, yWin;
	int xOld, yOld;
	int xNew, yNew;

	if (bStretched)
	{
		cxNewSize = cxWinSize - 2 * MARGIN;
		cyNewSize = cyWinSize - 2 * MARGIN;

		/* stretch the image to it's window determined size */

		/* the following two are mathematically the same, but the first
		* has side-effects because of rounding
		*/
		/*      if ((cyNewSize / cxNewSize) > (cyImgSize / cxImgSize)) */
		if ((cyNewSize * cxImgSize) > (cyImgSize * cxNewSize))
		{
			cyNewSize = cxNewSize * cyImgSize / cxImgSize;
			cxImgPos = MARGIN;
			cyImgPos = (cyWinSize - cyNewSize) / 2;
		}
		else
		{
			cxNewSize = cyNewSize * cxImgSize / cyImgSize;
			cyImgPos = MARGIN;
			cxImgPos = (cxWinSize - cxNewSize) / 2;
		}

		if (cyNewSize > ((size_t)(-1)) / (cImgChannels * cxNewSize))
		{
			pStretchedImage = (BYTE *)malloc(cImgChannels * cxNewSize * cyNewSize);
			pImg = pStretchedImage;

			for (yNew = 0; yNew < cyNewSize; yNew++)
			{
				yOld = yNew * cyImgSize / cyNewSize;
				for (xNew = 0; xNew < cxNewSize; xNew++)
				{
					xOld = xNew * cxImgSize / cxNewSize;

					r = *(pbImage + cImgChannels * ((yOld * cxImgSize) + xOld) + 0);
					g = *(pbImage + cImgChannels * ((yOld * cxImgSize) + xOld) + 1);
					b = *(pbImage + cImgChannels * ((yOld * cxImgSize) + xOld) + 2);
					*pImg++ = r;
					*pImg++ = g;
					*pImg++ = b;
					if (cImgChannels == 4)
					{
						a = *(pbImage + cImgChannels * ((yOld * cxImgSize) + xOld)
							+ 3);
						*pImg++ = a;
					}
				}
			}

			/* calculate row-bytes */

			wImgRowBytes = cImgChannels * cxNewSize;
			wDIRowBytes = (WORD)((cDIChannels * cxWinSize + 3L) >> 2) << 2;

			/* copy image to screen */

			for (yImg = 0, yWin = cyImgPos; yImg < cyNewSize; yImg++, yWin++)
			{
				if (yWin >= cyWinSize - cyImgPos)
					break;
				src = pStretchedImage + yImg * wImgRowBytes;
				dst = pDiData + yWin * wDIRowBytes + cxImgPos * cDIChannels;

				for (xImg = 0, xWin = cxImgPos; xImg < cxNewSize; xImg++, xWin++)
				{
					if (xWin >= cxWinSize - cxImgPos)
						break;
					r = *src++;
					g = *src++;
					b = *src++;
					*dst++ = b; /* note the reverse order  */
					*dst++ = g;
					*dst++ = r;
					if (cImgChannels == 4)
					{
						a = *src++;
					}
				}
			}

			/* free memory */

			if (pStretchedImage != NULL)
			{
				free(pStretchedImage);
				pStretchedImage = NULL;
			}

		}
		else/* process the image not-stretched */
		{
			/* calculate the central position */

			cxImgPos = (cxWinSize - cxImgSize) / 2;
			cyImgPos = (cyWinSize - cyImgSize) / 2;

			/* check for image larger than window */

			if (cxImgPos < MARGIN)
				cxImgPos = MARGIN;
			if (cyImgPos < MARGIN)
				cyImgPos = MARGIN;

			/* calculate both row-bytes */

			wImgRowBytes = cImgChannels * cxImgSize;
			wDIRowBytes = (WORD)((cDIChannels * cxWinSize + 3L) >> 2) << 2;

			/* copy image to screen */

			for (yImg = 0, yWin = cyImgPos; yImg < cyImgSize; yImg++, yWin++)
			{
				if (yWin >= cyWinSize - MARGIN)
					break;
				src = pbImage + yImg * wImgRowBytes;
				dst = pDiData + yWin * wDIRowBytes + cxImgPos * cDIChannels;

				for (xImg = 0, xWin = cxImgPos; xImg < cxImgSize; xImg++, xWin++)
				{
					if (xWin >= cxWinSize - MARGIN)
						break;
					r = *src++;
					g = *src++;
					b = *src++;
					*dst++ = b; /* note the reverse order  */
					*dst++ = g;
					*dst++ = r;
					if (cImgChannels == 4)
					{
						a = *src++;
					}
				}
			}
		}

		return TRUE;
	}
	return FALSE;
}

BOOL PngLoadImage(PTSTR pstrFileName, png_byte **ppbImageData, unsigned int *piWidth, unsigned int *piHeight, int *piChannels, png_color *pBkgColor)
{
	FILE				*pfFile;
	png_byte            pbSig[8];
	int                 iBitDepth;
	int                 iColorType;
	double              dGamma;
	png_color_16       *pBackground;
	png_uint_32         ulChannels;
	png_uint_32         ulRowBytes;
	png_byte           *pbImageData = *ppbImageData;
	static png_byte   **ppbRowPointers = NULL;
	unsigned int                 i;
	static png_structp png_ptr = NULL;
	static png_infop info_ptr = NULL;

	/* open the PNG input file */

	if (!pstrFileName)
	{
		*ppbImageData = pbImageData = NULL;
		return FALSE;
	}
	if (0 != _tfopen_s(&pfFile, pstrFileName, _T("rb")))
	{
		*ppbImageData = pbImageData = NULL;
		return FALSE;
	}

	/* first check the eight byte PNG signature */

	fread(pbSig, 1, 8, pfFile);
	if (png_sig_cmp(pbSig, 0, 8))
	{
		*ppbImageData = pbImageData = NULL;
		return FALSE;
	}

	/* create the two png(-info) structures */

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		*ppbImageData = pbImageData = NULL;
		return FALSE;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		*ppbImageData = pbImageData = NULL;
		return FALSE;
	}

	{

		/* initialize the png structure */

#ifdef PNG_STDIO_SUPPORTED
		png_init_io(png_ptr, pfFile);
#else
		png_set_read_fn(png_ptr, (png_voidp)pfFile, png_read_data);
#endif

		png_set_sig_bytes(png_ptr, 8);

		/* read all PNG info up to image data */

		png_read_info(png_ptr, info_ptr);

		/* get width, height, bit-depth and color-type */

		png_get_IHDR(png_ptr, info_ptr, piWidth, piHeight, &iBitDepth,
			&iColorType, NULL, NULL, NULL);

		/* expand images of all color-type and bit-depth to 3x8-bit RGB */
		/* let the library process alpha, transparency, background, etc. */

#ifdef PNG_READ_16_TO_8_SUPPORTED
		if (iBitDepth == 16)
#  ifdef PNG_READ_SCALE_16_TO_8_SUPPORTED
			png_set_scale_16(png_ptr);
#  else
			png_set_strip_16(png_ptr);
#  endif
#endif
		if (iColorType == PNG_COLOR_TYPE_PALETTE)
			png_set_expand(png_ptr);
		if (iBitDepth < 8)
			png_set_expand(png_ptr);
		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
			png_set_expand(png_ptr);
		if (iColorType == PNG_COLOR_TYPE_GRAY ||
			iColorType == PNG_COLOR_TYPE_GRAY_ALPHA)
			png_set_gray_to_rgb(png_ptr);

		/* set the background color to draw transparent and alpha images over */
		if (png_get_bKGD(png_ptr, info_ptr, &pBackground))
		{
			png_set_background(png_ptr, pBackground, PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
			pBkgColor->red = (byte)pBackground->red;
			pBkgColor->green = (byte)pBackground->green;
			pBkgColor->blue = (byte)pBackground->blue;
		}
		else
		{
			pBkgColor = NULL;
		}

		/* if required set gamma conversion */
		if (png_get_gAMA(png_ptr, info_ptr, &dGamma))
			png_set_gamma(png_ptr, (double) 2.2, dGamma);

		/* after the transformations are registered, update info_ptr data */

		png_read_update_info(png_ptr, info_ptr);

		/* get again width, height and the new bit-depth and color-type */

		png_get_IHDR(png_ptr, info_ptr, piWidth, piHeight, &iBitDepth,
			&iColorType, NULL, NULL, NULL);


		/* row_bytes is the width x number of channels */

		ulRowBytes = png_get_rowbytes(png_ptr, info_ptr);
		ulChannels = png_get_channels(png_ptr, info_ptr);

		*piChannels = ulChannels;

		/* now we can allocate memory to store the image */

		if (pbImageData)
		{
			free(pbImageData);
			pbImageData = NULL;
		}
		//if ((*piHeight) > ((size_t)(-1)) / ulRowBytes) 
		{
			{
				//png_error(png_ptr, "Visual PNG: image is too big");
			}
			if ((pbImageData = (png_byte *)malloc(ulRowBytes * (*piHeight)
				* sizeof(png_byte))) == NULL)
			{
				png_error(png_ptr, "Visual PNG: out of memory");
			}
			*ppbImageData = pbImageData;

			/* and allocate memory for an array of row-pointers */

			if ((ppbRowPointers = (png_bytepp)malloc((*piHeight)
				* sizeof(png_bytep))) == NULL)
			{
				png_error(png_ptr, "Visual PNG: out of memory");
			}

			/* set the individual row-pointers to point at the correct offsets */

			for (i = 0; i < (*piHeight); i++)
				ppbRowPointers[i] = pbImageData + i * ulRowBytes;

			/* now we can go ahead and just read the whole image */

			png_read_image(png_ptr, ppbRowPointers);

			/* read the additional chunks in the PNG file (not really needed) */

			png_read_end(png_ptr, NULL);

			/* and we're done */

			free(ppbRowPointers);
			ppbRowPointers = NULL;

			/* yepp, done */
		}


		{
			png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

			*ppbImageData = pbImageData = NULL;

			if (ppbRowPointers)
				free(ppbRowPointers);

			fclose(pfFile);

			return FALSE;
		}

		fclose(pfFile);

		return TRUE;
	}
}


BOOL DisplayImage(HWND hwnd, BYTE **ppDib,
	BYTE **ppDiData, int cxWinSize, int cyWinSize,
	BYTE *pbImage, int cxImgSize, int cyImgSize, int cImgChannels,
	BOOL bStretched)
{
	BYTE                       *pDib = *ppDib;
	BYTE                       *pDiData = *ppDiData;
	/* BITMAPFILEHEADER        *pbmfh; */
	BITMAPINFOHEADER           *pbmih;
	WORD                        wDIRowBytes;
	png_color                   bkgBlack = { 0, 0, 0 };
	png_color                   bkgGray = { 127, 127, 127 };
	png_color                   bkgWhite = { 255, 255, 255 };

	/* allocate memory for the Device Independant bitmap */

	wDIRowBytes = (WORD)((3 * cxWinSize + 3L) >> 2) << 2;

	if (pDib)
	{
		free(pDib);
		pDib = NULL;
	}

	//if (cyWinSize > ((size_t)(-1)) / wDIRowBytes) 
	{

		if (!(pDib = (BYTE *)malloc(sizeof(BITMAPINFOHEADER) +
			wDIRowBytes * cyWinSize)))
		{
			*ppDib = pDib = NULL;
			return FALSE;
		}
		*ppDib = pDib;
		memset(pDib, 0, sizeof(BITMAPINFOHEADER));

		/* initialize the dib-structure */

		pbmih = (BITMAPINFOHEADER *)pDib;
		pbmih->biSize = sizeof(BITMAPINFOHEADER);
		pbmih->biWidth = cxWinSize;
		pbmih->biHeight = -((long)cyWinSize);
		pbmih->biPlanes = 1;
		pbmih->biBitCount = 24;
		pbmih->biCompression = 0;
		pDiData = pDib + sizeof(BITMAPINFOHEADER);
		*ppDiData = pDiData;

		/* first fill bitmap with gray and image border */

		InitBitmap(pDiData, cxWinSize, cyWinSize);

		/* then fill bitmap with image */

		if (pbImage)
		{
			FillBitmap(
				pDiData, cxWinSize, cyWinSize,
				pbImage, cxImgSize, cyImgSize, cImgChannels,
				bStretched);
		}

		return TRUE;
	}
	return FALSE;
}



