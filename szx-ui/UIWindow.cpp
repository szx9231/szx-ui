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


LRESULT UIWindow::HandleMessages(UINT message, WPARAM wParam, LPARAM lParam)
{
	bool isStopPropagation = false;
	switch (message)
	{
	case WM_PAINT:
		OnPaint();
		isStopPropagation = true;
		break;
	default:
		break;
	}

	return isStopPropagation ? 0 : __super::HandleMessages(message, wParam, lParam);
}

void UIWindow::OnPaint()
{
	PAINTSTRUCT ps;
	HDC hdc = ::BeginPaint(m_hwnd, &ps);

	RECT rect;
	GetClientRect(m_hwnd,&rect);
	
	UIRender* uiRender = UIRender::Instance();
	uiRender->BeginPaint(hdc, rect.right - rect.left, rect.bottom - rect.top);

	if(m_rootControl)
	{
		m_rootControl->Render(&UIRect(rect));
	}

	uiRender->EndPaint();

	::EndPaint(m_hwnd, &ps);
}