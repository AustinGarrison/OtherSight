#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
		case WM_LBUTTONDOWN:
			MessageBoxW(hwnd, L"You Clicked!", L"Other Sight", MB_OK);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int showCommand) {

	const wchar_t className[] = L"OtherSightWindow";

	WNDCLASSEXW wc{};
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = instance;
	wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wc.lpszClassName = className;
	RegisterClassExW(&wc);

	HWND hwnd = CreateWindowExW(
		0,						// extended Styles
		className,				// which window class
		L"Other Sight",			// title bar
		WS_OVERLAPPEDWINDOW,	// normal window: title bar, border, min/max/close
		CW_USEDEFAULT,			// position
		CW_USEDEFAULT,			// position
		800, 600,				// size
		nullptr,				// parent window
		nullptr,				// menu
		instance,
		nullptr
	);

	if (hwnd == nullptr)
		return 1;

	ShowWindow(hwnd, showCommand);

	MSG msg{};
	while (GetMessageW(&msg, nullptr, 0, 0) > 0) 
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return static_cast<int>(msg.wParam);
}