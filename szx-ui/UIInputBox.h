#pragma once
#include "UIControl.h"
#include "NativeWindow.h"

#include <string>

/*
* �����
* ȡ������û�л�ý��㣬
* ����н���Ļ�����������λ����Ⱦһ��win32��Edit�ؼ�
* û�н���Ļ�����GDI��һ�����ο򣬾��ο��м仭����
*/
class UIInputBoxWindow;
class UIInputBox : public UIControl
{
public:
    UIInputBox(UIWindow* parentWindow);
    virtual ~UIInputBox(void);
public:
    virtual void SetAttribute(const std::wstring& wstrName, const std::wstring& wstrValue);
    virtual void RenderSelf(UIRect* rect);

private:
    std::wstring m_wstrPlaceHolder;
    std::wstring m_wstrValue;
    friend class UIInputBoxWindow;
    UIInputBoxWindow* m_ptrInputBoxWindow;
};

/*
 *	�н����ʱ��һ��win32��edit����������
 */
class UIInputBoxWindow : public NativeWindow
{
public:
    void Init(UIInputBox* ptrInputBox);
    virtual wchar_t* GetWindowClassName() {return L"inputbox_window";}
    virtual const wchar_t* GetSuperClassName() const {return L"Edit";}
    virtual LRESULT	HandleMessages(UINT message, WPARAM wParam, LPARAM lParam);
};

