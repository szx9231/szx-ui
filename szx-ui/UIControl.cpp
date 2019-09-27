#include "stdafx.h"
#include "UIControl.h"

#include <stdio.h>
#include <assert.h>

UIControl::UIControl(UIWindow* parentWindow)
    : m_parentWindow(parentWindow), m_parentControl(NULL)
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
    else if(wstrName == L"position")
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
    HWND hwnd = m_parentWindow->GetHWND();
    HDC hdc = ::GetDC(hwnd);

    UIRender::Instance()->SelectClipedRect(&rect);
    RenderSelf(&rect);

    for(auto iter : m_children)
    {
        iter->Render(&rect);
    }
}

void UIControl::RenderSelf(UIRect* rect)
{
    assert(rect != NULL);
}

UIControl* UIControl::FindControlByPosition(const UIPoint& point)
{
    UIControl* targetControl = this;

    for(auto child : m_children)
    {
        if(child->IsMouseInControl(point))
        {
            targetControl = child->FindControlByPosition(point);
            break;
        }
    }

    return targetControl;
}

BOOL UIControl::IsMouseInControl(const UIPoint& point)
{
    return ::PtInRect(&m_rectPosition, point);
}

BOOL UIControl::DispathMouseMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
  if(OnMouseMessage(message, wParam, lParam) == FALSE)
  {
	  UIControl* parentControl = GetParentControl();
	  if(parentControl)
	  {
		  parentControl->DispathMouseMessage(message, wParam, lParam);
	  }
	  
  }

  return TRUE;
}

BOOL UIControl::OnLButtonDown(UINT flag, const UIPoint &point)
{
	return FALSE;
}

BOOL UIControl::OnMouseMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	UIPoint	point((short)LOWORD(lParam), (short)HIWORD(lParam));
	UINT flag = (UINT)wParam;

	BOOL messageHandled = FALSE;
	switch(message)
	{
	case WM_LBUTTONDOWN:
		messageHandled = OnLButtonDown(flag, point);
		break;

	default:
		break;
	}

	return messageHandled;
}