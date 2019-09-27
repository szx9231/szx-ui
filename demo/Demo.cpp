#include <Windows.h>
#include "../szx-ui/NativeWindow.h"
#include "../szx-ui/UIWindow.h"
#include "../szx-ui/UIInputBox.h"

class MainWindow : public UIWindow
{

};

//解决
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
    MainWindow mainWindow;
    mainWindow.Create(NULL, L"主窗口", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, CW_USEDEFAULT, CW_USEDEFAULT, 300, 350);
	mainWindow.AsRootWindow();
    mainWindow.ShowWindow(TRUE, TRUE);

    UIControl* control = new UIInputBox(&mainWindow);
    control->SetAttribute(L"name", L"control");
    control->SetAttribute(L"size", L"200 30");
    control->SetAttribute(L"position", L"10 10 210 40");
    control->SetAttribute(L"value", L"please input some text~");

    mainWindow.AddRootControl(control);

    MSG msg;
    BOOL bRet;
    while((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if(bRet == -1)
        {
            break;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return 0;
}