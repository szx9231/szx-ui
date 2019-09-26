#include "stdafx.h"
#include "UIControl.h"

#include <stdio.h>
#include <assert.h>

UIControl::UIControl(void)
{
}


UIControl::~UIControl(void)
{
	for(auto iter : m_children)
	{
		delete iter;
	}
}


void UIControl::SetAttribute(const std::wstring& wstrName, const std::wstring& wstrValue)
{
	if(wstrName == L"name")
	{
		m_wstrName = wstrValue;
	}
	else if(wstrName == L"id")
	{
		m_id = std::stoi(wstrValue);
	}
	else if(wstrName == L"size")
	{
		int width, height;
		swscanf_s(wstrValue.c_str(), L"%d %d", &width, &height);
		m_size.cx = width;
		m_size.cy = height;
	}
	else if (wstrName == L"position")
	{
		int left, top, right, bottom;
		swscanf_s(wstrValue.c_str(), L"%d %d %d %d", &left, &top, &right, &bottom);
		m_rectPosition.left = left;
		m_rectPosition.top = top;
		m_rectPosition.right = right;
		m_rectPosition.bottom = bottom;
	}
}

void UIControl::AppendChild(UIControl* ptrChildControl)
{
	assert(ptrChildControl != NULL);

	m_children.push_back(ptrChildControl);
}

void UIControl::Render(UIRect* rectWindow)
{
	// 生成该控件和窗口的交集区域
	UIRect rect = UIRect::IntersectRect(&m_rectPosition, rectWindow);
}