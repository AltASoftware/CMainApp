// Defines the entry point for the application.
// OFr actual use you need to derive from MainApp and do work.
//
#include "MainApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	CMainApp app(300,300, "Hello World");
	return app.Run(hInstance, nCmdShow);
	}
	
