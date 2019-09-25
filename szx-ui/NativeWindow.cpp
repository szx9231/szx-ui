#include "stdafx.h"
#include "NativeWindow.h"

#include <assert.h>

BOOL NativeWindow::RegisterWindowClass()
{
	WNDCLASSEX wcx = {0}; 
	wcx.cbSize = sizeof(WNDCLASSEX);							// size of structure 
	wcx.style = CS_HREDRAW | CS_VREDRAW;						// redraw if size changes 
	wcx.lpfnWndProc = NativeWindow::StaticHandleMessages;		// points to window procedure 
	wcx.cbClsExtra = 0;											// no extra class memory 
	wcx.cbWndExtra = 0;											// no extra window memory 
	wcx.hInstance = NULL;										// handle to instance 
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// predefined app. icon 
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);					// predefined arrow 
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// white background brush 
	wcx.lpszMenuName = NULL;									// name of menu resource 
	wcx.lpszClassName = GetWindowClassName();						// name of window class 
	wcx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);				// small class icon 

	return RegisterClassEx(&wcx) != 0 || 
		::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

BOOL NativeWindow::RegisterSuperClass()
{
	WNDCLASSEX wcx = {0};
	wcx.cbSize = sizeof(WNDCLASSEX);
	if(!::GetClassInfoEx(NULL, GetSuperClassName(), &wcx))
	{
		return FALSE;
	}

	m_oldWindowProc = wcx.lpfnWndProc;
	wcx.lpfnWndProc = NativeWindow::StaticHandleMessages;
	wcx.hInstance = NULL;
	wcx.lpszClassName = GetWindowClassName();
	ATOM result = ::RegisterClassEx(&wcx);
	return result != NULL || ::GetLastError() == ERROR_CLASS_ALREADY_EXISTS;
}

BOOL NativeWindow::Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, 
						  int x /* = CW_USEDEFAULT */, int y /* = CW_USEDEFAULT */, int cx /* = CW_USEDEFAULT */, int cy /* = CW_USEDEFAULT */,
						  HMENU hMenu /* = NULL */)
{
	if(GetSuperClassName())
	{
		if(!RegisterSuperClass())
		{
			return FALSE;
		}
	}
	else
	{
		if(!RegisterWindowClass())
		{
			return FALSE;
		}
	}

	wchar_t* wstrWindowClassName = GetWindowClassName();
	m_hwnd = ::CreateWindowEx(dwExStyle, wstrWindowClassName, pstrName, dwStyle, x, y, cx, cy, hwndParent, hMenu, NULL, this);

	BOOL created = FALSE;
	if(m_hwnd == NULL)
	{
		created = OnWindowCreated();
	}

	return created;
}

BOOL NativeWindow::Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu /* = NULL */)
{
	return NativeWindow::Create(hwndParent, pstrName, dwStyle, dwExStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom -rc.top, hMenu);
}

LRESULT NativeWindow::StaticHandleMessages(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 获取对象指针
	if (message == WM_NCCREATE)
	{
		CREATESTRUCT *lpcs = (CREATESTRUCT*)lParam;
		NativeWindow* nativeWindow = reinterpret_cast<NativeWindow*>(lpcs->lpCreateParams);

		nativeWindow->m_hwnd = hwnd;
		SetWindowLong(hwnd, GWL_USERDATA, (LPARAM)nativeWindow);
	}
	else if(message == WM_NCDESTROY)
	{
		NativeWindow* nativeWindow = reinterpret_cast<NativeWindow*>(::GetWindowLong(hwnd, GWL_USERDATA));
		if(nativeWindow)
		{
			LRESULT result = ::CallWindowProc(nativeWindow->m_oldWindowProc, hwnd, message, wParam, lParam);
			::SetWindowLongPtr(nativeWindow->GetHWND(), GWLP_USERDATA, 0L);
			nativeWindow->OnDestroy();
			return result;
		}
	}

	NativeWindow* nativeWindow = (NativeWindow*)(::GetWindowLong(hwnd, GWL_USERDATA));
	if(nativeWindow)
	{
		return nativeWindow->HandleMessages(message, wParam, lParam);
	}
	else
	{
		return ::DefWindowProc(hwnd, message, wParam, lParam);
	}
}

LRESULT NativeWindow::HandleMessages(UINT message, WPARAM wParam, LPARAM lParam)
{
	return CallWindowProc(m_oldWindowProc, m_hwnd, message, wParam, lParam);
}

void NativeWindow::ShowWindow(BOOL show, BOOL takeFocus)
{
	assert(::IsWindow(m_hwnd));
	if( !::IsWindow(m_hwnd) ) 
		return;
	::ShowWindow(m_hwnd, show ? (takeFocus ? SW_SHOWNORMAL : SW_SHOWNOACTIVATE) : SW_HIDE);
}

BOOL NativeWindow::OnDestroy()
{
	::PostQuitMessage(0);
	return TRUE;
}

BOOL NativeWindow::OnWindowCreated()
{
	return TRUE;
}