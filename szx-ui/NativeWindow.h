#pragma once

#include <windows.h>

/************************************************************************/
/* win32的注册、创建窗口的封装                                              */
/************************************************************************/
class NativeWindow 
{
public:
	NativeWindow():m_hwnd(NULL), m_oldWindowProc(::DefWindowProc){};
	virtual ~NativeWindow(){};

public:
	BOOL RegisterWindowClass();
	BOOL RegisterSuperClass();
	HWND GetHWND() {return m_hwnd;}

	BOOL Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
	BOOL Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, 
		int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);

	void ShowWindow(BOOL show, BOOL takeFocus);

	virtual wchar_t* GetWindowClassName() {return L"native_window";}
	virtual const wchar_t* GetSuperClassName() const  {return NULL;}

	// native window创建成功之后的回调，在这个回调中设置子控件
	virtual BOOL OnWindowCreated();

	virtual BOOL OnDestroy();
public:
	// static函数，喂给窗口注册
	static LRESULT CALLBACK StaticHandleMessages(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	// 自定义消息处理函数，所有消息在这里分发
	virtual LRESULT	HandleMessages(UINT message, WPARAM wParam, LPARAM lParam);

protected:
	WNDPROC m_oldWindowProc;
	HWND m_hwnd;
};