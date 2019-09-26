#pragma once
#include "UIBase.h"
#include <vector>
#include <string>

class UIControl
{
public:
	UIControl(void);
	virtual ~UIControl(void);
public:
	void SetAttribute(const std::wstring& wstrName, const std::wstring& wstrValue);

	//TODO: ��weakptr���ָ��ʧЧ����
	void AppendChild(UIControl* ptrChildControl);

	// �����ڵ��ã������ؼ���Ⱦ
	void Render(UIRect* rectWindow);

	// ÿ���ؼ������Ⱦ
	virtual void RenderSelf(UIRect* rect);
private:
	std::wstring m_wstrName;// �ؼ�����
	int m_id;// �ؼ�ID
	UIRect m_rectPosition;// �ؼ�λ��(����ڸ�����)
	UISize m_size;// �ؼ��ߴ�
	std::vector<UIControl*> m_children;// �ӿؼ�
};

