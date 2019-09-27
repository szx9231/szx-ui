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
        UIControl* GetParentControl() {return m_parentControl;}
        void SetParentControl(UIControl* parentControl) {m_parentControl = parentControl;}
        //TODO: ��weakptr���ָ��ʧЧ����
        void AppendChild(UIControl* ptrChildControl);

        UIControl* FindControlByPosition(const UIPoint& point);

        BOOL IsMouseInControl(const UIPoint& point);

        BOOL DispathMouseMessage(UINT message, WPARAM wParam, LPARAM lParam);

        BOOL OnMouseMessage(UINT message, WPARAM wParam, LPARAM lParam);

        // �����ڵ��ã������ؼ���Ⱦ
        void Render(UIRect* rectWindow);

        // ÿ���ؼ������Ⱦ
        virtual void RenderSelf(UIRect* rect);

        virtual	BOOL OnLButtonDown(UINT flag, const UIPoint &point);
    private:
        std::wstring m_wstrName;// �ؼ�����
        int m_id;// �ؼ�ID
        UIRect m_rectPosition;// �ؼ�λ��(����ڸ�����)
        UISize m_size;// �ؼ��ߴ�
        std::vector<UIControl*> m_children;// �ӿؼ�
        UIWindow* m_parentWindow;// ���ڣ�ֻ�и��ؼ�����
        UIControl* m_parentControl;// ���ؼ�
};

