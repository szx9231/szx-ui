#pragma once
#include "UIBase.h"
#include "UIWindow.h"

#include <vector>
#include <string>

class UIControl
{
public:
    UIControl(UIWindow* parentWindow);
    virtual ~UIControl(void);
public:
    virtual void SetAttribute(const std::wstring& wstrName, const std::wstring& wstrValue);

    UIWindow* GetParentWindow() {return m_parentWindow;}
    UIRect GetPositionRect() {return m_rectPosition;}
    //TODO: 用weakptr解决指针失效问题
    void AppendChild(UIControl* ptrChildControl);

    // 被窗口调用，触发控件渲染
    void Render(UIRect* rectWindow);

    // 每个控件如何渲染
    virtual void RenderSelf(UIRect* rect);
private:
    std::wstring m_wstrName;// 控件名字
    int m_id;// 控件ID
    UIRect m_rectPosition;// 控件位置(相对于父窗口)
    UISize m_size;// 控件尺寸
    std::vector<UIControl*> m_children;// 子控件
    UIWindow* m_parentWindow;
};

