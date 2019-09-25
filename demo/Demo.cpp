#include <Windows.h>
#include "../szx-ui/NativeWindow.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	NativeWindow nativeWindow;
	nativeWindow.Create(NULL,L"Ö÷´°¿Ú",WS_OVERLAPPEDWINDOW | WS_VISIBLE,0,CW_USEDEFAULT,CW_USEDEFAULT,300,350);
	nativeWindow.ShowWindow(TRUE, TRUE);

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