#include "stdafx.h"
#include "XKnowRender.h"

CXKnowFontManager* CXKnowFontManager::m_pFontManager = new CXKnowFontManager();
/*
���ϲ���һ��, ��̬��map��Ա��ȫ�ֵ�, cpp��ʹ��ǰ����������һ��.����������������������.�ο����������:http://blog.sina.com.cn/s/blog_6daadb2f0100re2z.html
.h
class   ClassName
{
static   map<DWORD, HBRUSH>   g_mapEditBrush;
}
.cpp
map<DWORD, HBRUSH>   ClassName::g_mapEditBrush;*/