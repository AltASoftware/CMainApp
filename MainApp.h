#pragma once

//
// This will be the encapsulation of a basic windows 32 App.
//
class CMainApp
{
public:
	CMainApp(UINT width, UINT height, std::wstring name);
	virtual ~CMainApp();

	int Run(HINSTANCE hInstance, int nCmdShow);

protected:
	// Viewport dimensions.
	UINT m_width;
	UINT m_height;
	float m_aspectRatio;

	HWND m_hwnd; // Window handle.

	bool m_useWarpDevice; // Adapter info.

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	virtual bool OnEvent(MSG msg) { return true; };
	virtual void OnUpdate() {};
	virtual void OnRender() {};
	virtual void OnDestroy() {};

private:
	std::wstring m_title; //Window title.

	void ParseCommandLineArgs();
};
