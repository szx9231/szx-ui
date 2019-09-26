#pragma once
#include "UIBase.h"

class UIRender
{
public:
	UIRender(HDC hdc,int width,int height);
	~UIRender(void);

	void Text(const wchar_t *text,size_t text_length,
		const UIRect *rect,UIColor text_color,UINT format,const UIFont *font = NULL);

	void Rectangle(const UIRect *rect,UIColor color);
	void SelectClipedRect(const UIRect *rect);	

private:
	HDC m_hdcMem;
	HDC m_hdcSrc;
	HBITMAP m_hBitmap;
	HBITMAP m_hBitmapOld;
	int m_width;
	int m_height;
};

