#pragma once
#include "stdafx.h"

extern "C"
{
	extern unsigned char *stbi_load_from_memory(unsigned char const *buffer, int len, int *x, int *y, \
		int *comp, int req_comp);
	extern void     stbi_image_free(void *retval_from_stbi_load);

};

HBITMAP LoadFile(LPCTSTR lpszFileName)
{
	HANDLE hFile = ::CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwSize = ::GetFileSize(hFile, NULL);
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

	BITMAPINFO bmi;
	::ZeroMemory(&bmi, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biWidth = x;
	bmi.bmiHeader.biHeight = -y;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = x * y * 4;

	LPBYTE pDest = NULL;
	HBITMAP hBitmap = ::CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void **)&pDest, NULL, 0);

	for (int i = 0; i < x * y; i++)
	{
		pDest[i * 4 + 3] = pImage[i * 4 + 3];
		if (pDest[i * 4 + 3] < 255)
		{
			pDest[i * 4] = (BYTE)(DWORD(pImage[i * 4 + 2])*pImage[i * 4 + 3] / 255);
			pDest[i * 4 + 1] = (BYTE)(DWORD(pImage[i * 4 + 1])*pImage[i * 4 + 3] / 255);
			pDest[i * 4 + 2] = (BYTE)(DWORD(pImage[i * 4])*pImage[i * 4 + 3] / 255);
		}
		else
		{
			pDest[i * 4] = pImage[i * 4 + 2];
			pDest[i * 4 + 1] = pImage[i * 4 + 1];
			pDest[i * 4 + 2] = pImage[i * 4];
		}
	}
	stbi_image_free(pImage);


	return hBitmap;
}

