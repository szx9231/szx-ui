#include "stdafx.h"
#include "UIRender.h"
#include <assert.h>

UIRender::UIRender(HDC hdc,int width,int height)
	: m_hdcSrc(hdc), m_width(width), m_height(height)
{
	m_hdcMem	= CreateCompatibleDC(m_hdcSrc);
	m_hBitmap		= CreateCompatibleBitmap(m_hdcSrc,m_width,m_height);
	m_hBitmapOld	= (HBITMAP)SelectObject(m_hdcMem,m_hBitmap);
	BitBlt(m_hdcMem,0,0,m_width,m_height,m_hdcSrc,0,0,WHITENESS);
}


UIRender::~UIRender(void)
{
	BitBlt(m_hdcSrc,0,0,m_width,m_height,m_hdcMem,0,0,SRCCOPY);
	SelectObject(m_hdcSrc,m_hBitmapOld);
	DeleteDC(m_hdcMem);
	DeleteObject(m_hBitmap);
}

void UIRender::Text(const wchar_t *text,size_t text_length,
						const UIRect *rect,UIColor text_color,UINT format,const UIFont *font /* = NULL */)
{
	HFONT old_font = NULL;
	HFONT current_font = NULL;
	if (font)
	{
		current_font = CreateFontIndirect(font);
		old_font = (HFONT)SelectObject(m_hdcMem, current_font);
	}


	SetBkMode(m_hdcMem,TRANSPARENT);
	UIColor old_text_color = ::SetTextColor(m_hdcMem,text_color);

	::DrawText(m_hdcMem,text,(int)text_length,&rect->ToRect(),format);

	if (old_font && current_font)
	{
		::SelectObject(m_hdcMem,old_font);
		::DeleteObject(current_font);
	}

	::SetTextColor(m_hdcMem,old_text_color);
}

void UIRender::Rectangle(const UIRect *rect,UIColor color)
{
	LOGBRUSH lb = {BS_NULL};
	HBRUSH brush = CreateBrushIndirect(&lb);
	HBRUSH old_brush = (HBRUSH)::SelectObject(m_hdcMem,brush);
	HPEN pen = CreatePen(PS_SOLID,1,color);
	HPEN old_pen = (HPEN)::SelectObject(m_hdcMem,pen);
	::Rectangle(m_hdcMem,rect->left,rect->top,rect->right,rect->bottom);
	::SelectObject(m_hdcMem,old_brush);
	::SelectObject(m_hdcMem,old_pen);
	::DeleteObject(brush);
	::DeleteObject(pen);
}

void UIRender::SelectClipedRect(const UIRect *rect)
{
	assert(rect != NULL);

	HRGN hrgn = ::CreateRectRgnIndirect(rect);
	::SelectClipRgn(m_hdcMem, hrgn);
	::DeleteObject(hrgn);
}