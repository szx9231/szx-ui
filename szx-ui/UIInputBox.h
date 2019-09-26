#pragma once
#include "UIControl.h"
#include "NativeWindow.h"

#include <string>

/*
* 输入框，
* 取决于有没有获得焦点，
* 如果有焦点的话，在输入框的位置渲染一个win32的Edit控件
* 没有焦点的话，用GDI画一个矩形框，矩形框中间画文字
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
 *	有焦点的时候画一个win32的edit来处理输入
 */
class UIInputBoxWindow : public NativeWindow
{
public:
    void Init(UIInputBox* ptrInputBox);
    virtual wchar_t* GetWindowClassName() {return L"inputbox_window";}
    virtual const wchar_t* GetSuperClassName() const {return L"Edit";}
    virtual LRESULT	HandleMessages(UINT message, WPARAM wParam, LPARAM lParam);
};

