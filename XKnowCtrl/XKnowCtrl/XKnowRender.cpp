#include "stdafx.h"
#include "XKnowRender.h"

CXKnowFontManager* CXKnowFontManager::m_pFontManager = new CXKnowFontManager();
/*
网上查了一下, 静态的map成员是全局的, cpp中使用前必须再声明一次.看起来好象是声明了两次.参考下面的例子:http://blog.sina.com.cn/s/blog_6daadb2f0100re2z.html
.h
class   ClassName
{
static   map<DWORD, HBRUSH>   g_mapEditBrush;
}
.cpp
map<DWORD, HBRUSH>   ClassName::g_mapEditBrush;*/

extern "C"
{
	extern unsigned char *stbi_load_from_memory(unsigned char const *buffer, int len, int *x, int *y, int *comp, int req_comp);
	extern void     stbi_image_free(void *retval_from_stbi_load);

};
