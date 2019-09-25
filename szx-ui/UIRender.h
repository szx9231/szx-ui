#pragma once
#include "UIBase.h"

class UIRender
{
public:
	UIRender(void);
	~UIRender(void);

	static void Text(HDC hdc,const wchar_t *text,size_t text_length,
		const UIRect *rect,UIColor text_color,UINT format,const UIFont *font = NULL);

	static void Rectangle(HDC hdc, const UIRect *rect,UIColor color);
};

