#include "stdafx.h"
#include "UIWindow.h"
#include "UIRender.h"
#include "UIBase.h"
#include "UIControl.h"

#include <string>

UIWindow::UIWindow(void)
    : m_rootControl(NULL)
{
}


UIWindow::~UIWindow(void)
{
    delete m_rootControl;
}

void UIWindow::AddRootControl(UIControl* pUIControl)
{
    delete m_rootControl;
    m_rootControl = pUIControl;
}

/*
 *	鼠标消息：
 *	1.根据鼠标位置找到对应控件
 *	2.转发消息给该控件
 *	3.控件处理完毕再把消息向上传播
 */
LRESULT UIWindow::HandleMessages(UINT message, WPARAM wParam, LPARAM lParam)
{
    bool isStopPropagation = false;

    switch(message)
    {
        case WM_PAINT:
        {
            OnPaint();
            isStopPropagation = true;
            break;
        }

        case WM_MOUSELEAVE:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDBLCLK:
        case WM_MOUSEWHEEL:
        {
            OnMouseMessage(message, wParam, lParam);
        }

        default:
            break;
    }

    return isStopPropagation ? 0 : __super::HandleMessages(message, wParam, lParam);
}

void UIWindow::OnMouseMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    if(message == WM_LBUTTONDOWN)
    {
        ::SetFocus(m_hwnd);
    }

    if(m_rootControl)
    {
        UIPoint	point((short)LOWORD(lParam), (short)HIWORD(lParam));
        UIControl* targetControl = m_rootControl->FindControlByPosition(point);
		targetControl->DispathMouseMessage(message, wParam, lParam);
    }
}

void UIWindow::OnPaint()
{
    PAINTSTRUCT ps;
    HDC hdc = ::BeginPaint(m_hwnd, &ps);

    RECT rect;
    GetClientRect(m_hwnd, &rect);

    UIRender* uiRender = UIRender::Instance();
    uiRender->BeginPaint(hdc, rect.right - rect.left, rect.bottom - rect.top);

    if(m_rootControl)
    {
        m_rootControl->Render(&UIRect(rect));
    }

    uiRender->EndPaint();

    ::EndPaint(m_hwnd, &ps);
}