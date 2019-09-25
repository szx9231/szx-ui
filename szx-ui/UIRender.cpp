#include "stdafx.h"
#include "UIRender.h"


UIRender::UIRender(void)
{
}


UIRender::~UIRender(void)
{
}

void UIRender::Text(HDC hdc, const wchar_t *text,size_t text_length,
						const UIRect *rect,UIColor text_color,UINT format,const UIFont *font /* = NULL */)
{
	HFONT old_font = NULL;
	HFONT current_font = NULL;
	if (font)
	{
		current_font = CreateFontIndirect(font);
		old_font = (HFONT)SelectObject(hdc, current_font);
	}


	SetBkMode(hdc,TRANSPARENT);
	UIColor old_text_color = ::SetTextColor(hdc,text_color);

	::DrawText(hdc,text,(int)text_length,&rect->ToRect(),format);

	if (old_font && current_font)
	{
		::SelectObject(hdc,old_font);
		::DeleteObject(current_font);
	}

	::SetTextColor(hdc,old_text_color);
}

void UIRender::Rectangle(HDC hdc, const UIRect *rect,UIColor color)
{
	LOGBRUSH lb = {BS_NULL};
	HBRUSH brush = CreateBrushIndirect(&lb);
	HBRUSH old_brush = (HBRUSH)::SelectObject(hdc,brush);
	HPEN pen = CreatePen(PS_SOLID,1,color);
	HPEN old_pen = (HPEN)::SelectObject(hdc,pen);
	::Rectangle(hdc,rect->left,rect->top,rect->right,rect->bottom);
	::SelectObject(hdc,old_brush);
	::SelectObject(hdc,old_pen);
	::DeleteObject(brush);
	::DeleteObject(pen);
}
