#pragma once

#include <windows.h>

/************************************************************************/
/* win32��ע�ᡢ�������ڵķ�װ                                              */
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

	// native window�����ɹ�֮��Ļص���������ص��������ӿؼ�
	virtual BOOL OnWindowCreated();

	virtual BOOL OnDestroy();
public:
	// static������ι������ע��
	static LRESULT CALLBACK StaticHandleMessages(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	// �Զ�����Ϣ��������������Ϣ������ַ�
	virtual LRESULT	HandleMessages(UINT message, WPARAM wParam, LPARAM lParam);

protected:
	WNDPROC m_oldWindowProc;
	HWND m_hwnd;
};