#include "stdafx.h"
#include "UIBase.h"
#include "UIInputBox.h"
#include "UIRender.h"

#include <assert.h>
#include <windowsx.h>

UIInputBox::UIInputBox(UIWindow* parentWindow)
    : UIControl(parentWindow)
{
}


UIInputBox::~UIInputBox(void)
{
}


void UIInputBox::RenderSelf(UIRect* rect)
{
    COLORREF colorrrefRGB = RGB(0, 0, 0);
    UIRender::Instance()->Rectangle(rect, colorrrefRGB);

    if(m_wstrValue.length() != 0)
    {
        UIColor stringColor = RGB(0, 0, 0);
        UIRender::Instance()->Text(m_wstrValue.c_str(), m_wstrValue.length(), rect, stringColor, DT_SINGLELINE | DT_NOPREFIX | DT_EDITCONTROL);
    }
    else if(m_wstrPlaceHolder.length() != 0)
    {
        UIColor placeHolderColor = RGB(100, 100, 100);
        UIRender::Instance()->Text(m_wstrPlaceHolder.c_str(), m_wstrPlaceHolder.length(), rect, placeHolderColor, DT_SINGLELINE | DT_NOPREFIX | DT_EDITCONTROL);
    }

    if(m_ptrInputBoxWindow == NULL)
    {
        m_ptrInputBoxWindow = new UIInputBoxWindow();
        m_ptrInputBoxWindow->Init(this);
    }

}

void UIInputBox::SetAttribute(const std::wstring& wstrName, const std::wstring& wstrValue)
{
    __super::SetAttribute(wstrName, wstrValue);

    if(wstrName == L"placeholder")
    {
        m_wstrPlaceHolder = wstrValue;
    }
    else if(wstrName == L"value")
    {
        m_wstrValue = wstrValue;
    }
}

//////////////////////////////////////////////////////////////////////////


UIFont *GetGlobalEditFont()
{
    static UIFont *global_font = NULL;

    if(global_font == NULL)
    {
        global_font = new UIFont();
        memset(global_font, 0, sizeof(UIFont));
        global_font->lfHeight				= -15;
        global_font->lfWeight				= FW_NORMAL;
        global_font->lfOutPrecision			= OUT_STROKE_PRECIS;
        global_font->lfClipPrecision		= CLIP_STROKE_PRECIS;
        global_font->lfQuality				= DEFAULT_QUALITY;
        global_font->lfPitchAndFamily		= VARIABLE_PITCH | FF_SWISS;
        wcscpy_s(global_font->lfFaceName, L"SimSum");
    }

    return global_font;
}

void UIInputBoxWindow::Init(UIInputBox* ptrInputBox)
{
    assert(ptrInputBox);

    m_ptrInputbox = ptrInputBox;

    UIRect rect = ptrInputBox->GetPositionRect();
    rect.Deflate(1, 3);
    DWORD style = WS_CHILD | ES_AUTOHSCROLL;
    Create(ptrInputBox->GetParentWindow()->GetHWND(), NULL, style, NULL, rect);

    HWND hwnd = GetHWND();
    HFONT font = ::CreateFontIndirect(GetGlobalEditFont());
    SetWindowFont(hwnd, font, TRUE);

    ::SetWindowText(hwnd, ptrInputBox->m_wstrValue.c_str());
    Edit_SetModify(hwnd, TRUE);
    ::SendMessage(hwnd, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(2, 2));
    Edit_SetSel(hwnd, 0, -1);
    ::ShowWindow(hwnd, SW_SHOWNOACTIVATE);
    ::SetFocus(hwnd);


}

LRESULT UIInputBoxWindow::HandleMessages(UINT message, WPARAM wParam, LPARAM lParam)
{
    assert(m_ptrInputbox != NULL);

    switch(message)
    {
        case WM_KILLFOCUS:
        {
            std::wstring wstrWindowText;
            GetWindowText(wstrWindowText);
            m_ptrInputbox->SetTextValue(wstrWindowText);
            PostMessage(WM_CLOSE);
            break;
        }

        default:
            break;
    }

    return __super::HandleMessages(message, wParam, lParam);
}

BOOL UIInputBoxWindow::OnDestroy()
{
	__super::OnDestroy();
	m_ptrInputbox->m_ptrInputBoxWindow = NULL;
	delete this;
	return TRUE;
}