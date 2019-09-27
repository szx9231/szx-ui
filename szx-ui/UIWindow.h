#pragma once
#include "NativeWindow.h"
#include "UIRender.h"

class UIControl;
/*
 * \brief һ�������а����ܶ�ؼ����ô��ڸ�������������пؼ�
 *	ÿ���µĴ���Ӧ�ü̳и��࣬ÿ�������е���Ϣ���ɸô��ڷֵ�����Ӧ�Ŀؼ��������ϴ���
 *	�ؼ�֮������ݴ��俿�۲���ģʽ��ʵ�֣����ն��ɴ���ת����
 *	A�ؼ�֪ͨB�ؼ���A�ؼ�����һ���¼��������ڽ��ܵ���Ȼ��������е�listener��ÿ��listener�����¼�����
 *	���ж��Լ�Ҫ��Ҫ����
 * \author zhongxuan_sun
 * \date 09 2019
 * \params 
 */

class UIWindow : public NativeWindow
{
public:
	UIWindow(void);
	virtual~UIWindow(void);
public:
	virtual LRESULT HandleMessages(UINT message, WPARAM wParam, LPARAM lParam);
	void AddRootControl(UIControl* pUIControl);
	void OnPaint();
	void OnMouseMessage(UINT message, WPARAM wParam, LPARAM lParam);
	
public:
	UIControl* m_rootControl;
};

