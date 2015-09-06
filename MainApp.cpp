#include "stdafx.h"
#include "MainApp.h"

#include "resource.h"

#include <shellapi.h>


CMainApp::CMainApp(UINT width, UINT height, std::wstring name) :
	m_width(width),
	m_height(height),
	m_useWarpDevice(false),
	m_title(name)
{
	m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}


CMainApp::~CMainApp()
{
}

void CMainApp::ParseCommandLineArgs()
{
	int argc;
	LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	//Todo: Keeeping a bit of sample code to parse.
	for (int i = 1; i < argc; ++i)
	{
		if (_wcsnicmp(argv[i], L"-xxxx", wcslen(argv[i])) == 0 ||
			_wcsnicmp(argv[i], L"/xxxx", wcslen(argv[i])) == 0)
		{
			// option xxxx was set.
		}
	}
	LocalFree(argv);
}

int CMainApp::Run(HINSTANCE hInstance, int nCmdShow)
{
	// Initialize the window class.
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECT2DFIRSTSTEPS));
	windowClass.lpszMenuName = MAKEINTRESOURCEW(IDC_DIRECT2DFIRSTSTEPS);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszClassName = L"WindowClass1"; //Todo: Load from resource.
	RegisterClassEx(&windowClass);

	RECT windowRect = { 0, 0, static_cast<LONG>(m_width), static_cast<LONG>(m_height) };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	// Create the window and store a handle to it.
	m_hwnd = CreateWindowEx(NULL,
		L"WindowClass1", //Todo: This needs to cme from a resource.
		m_title.c_str(),
		WS_OVERLAPPEDWINDOW,
		300,
		300,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,		// We have no parent window, NULL.
		NULL,		// Optional menu parameter. Can be null even if using menus. We aren't using menus, NULL.
		hInstance,
		NULL);		// We aren't using multiple windows, NULL.

	ShowWindow(m_hwnd, nCmdShow); //Todo: need to check CreateWindow Succeeded.

								  // Main sample loop.
	MSG msg = { 0 };
	while (true)
	{
		// Process any messages in the queue.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;

			// Pass events into our sample.
			OnEvent(msg);
		}

		OnUpdate();
		OnRender();
	}

	OnDestroy();
	// Return this part of the WM_QUIT message to Windows.
	//return static_cast<char>(msg.wParam);
	return 0;
}

LRESULT CALLBACK CMainApp::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Main message handler
{
	// Handle destroy/shutdown messages.
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	// Handle any messages the switch statement didn't.
	return DefWindowProc(hWnd, message, wParam, lParam);
}
