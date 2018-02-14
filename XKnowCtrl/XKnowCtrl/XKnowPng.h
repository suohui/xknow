#pragma once
enum PNGTYPE
{
	TwoInOne,
	ThreeInOne,
	FourInOne
};
HBITMAP CreateHBitmapFromFile(LPCTSTR lpszFileName);
HBITMAP CreateHBitmapFromFile(LPCTSTR lpszFileName, int &iWidth, int &iHeight, BOOL &bAlpha);
