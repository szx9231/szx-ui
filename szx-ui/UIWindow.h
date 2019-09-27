#pragma once
#include "NativeWindow.h"
#include "UIRender.h"

class UIControl;
/*
 * \brief 一个窗口中包含很多控件，该窗口负责管理旗下所有控件
 *	每个新的窗口应该继承该类，每个窗口中的消息都由该窗口分到到对应的控件，并向上传播
 *	控件之间的数据传输靠观察者模式来实现，最终都由窗口转发。
 *	A控件通知B控件，A控件发送一个事件，被窗口接受到，然后调用所有的listener，每个listener根据事件类型
 *	来判断自己要不要处理
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

