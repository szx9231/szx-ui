#include <Windows.h>
#include "../szx-ui/NativeWindow.h"
#include "../szx-ui/UIWindow.h"

class MainWindow : public UIWindow
{

};

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	MainWindow mainWindow;
	mainWindow.Create(NULL,L"Ö÷´°¿Ú",WS_OVERLAPPEDWINDOW | WS_VISIBLE,0,CW_USEDEFAULT,CW_USEDEFAULT,300,350);
	mainWindow.ShowWindow(TRUE, TRUE);

	MSG msg;
	BOOL bRet;
	while((bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	{ 
		if (bRet == -1)
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