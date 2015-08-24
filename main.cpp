#include <Windows.h>
#include <ctime>
#include "game.h"
#include "Graphics.hpp"

using namespace std;

Game g;
const int ID_QUIT = 1;
const int ID_RESTART = 2;
const int ID_WIN = 3;
const int ID_ABOUT = 4;

HMENU createMenu() {

	HMENU main = CreateMenu();
	HMENU file = CreateMenu();
	HMENU help = CreateMenu();
	AppendMenu(file, MF_STRING, ID_RESTART, "Restart");
	AppendMenu(file, MF_STRING, ID_QUIT, "Quit");
	AppendMenu(main, MF_POPUP, (UINT_PTR)file, "&File");
	AppendMenu(main, MF_POPUP, (UINT_PTR)help, "&Help");
	AppendMenu(help, MF_STRING, ID_ABOUT, "About");
	return main;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps = { 0 };
	HDC hdc;

	switch (msg) {

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case ID_QUIT:
					PostQuitMessage(0);
					break;
				case ID_RESTART:
					if (MessageBox(hwnd, "Are you sure?", "Restart", MB_YESNO) == IDYES)
						InitializeGame(&g, hwnd);
					break;
				case ID_ABOUT:
					MessageBox(hwnd, "Objective: Shoot down your enemy before he shoots down you. First to 3 kills win", "Space Invaders", MB_OK);
					break;
			}
			break;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			break;

		case WM_CLOSE:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	char className[] = { "MyWindowClass" };
	int width = 400;
	int height = 400;

	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = 0;
	windowClass.lpfnWndProc = WinProc;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = (HICON)LoadIcon(0, IDI_ASTERISK);
	windowClass.hIconSm = NULL;
	windowClass.hCursor = (HCURSOR)LoadCursor(0, IDC_ARROW);
	windowClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = className;

	/* register window */
	RegisterClassEx(&windowClass);

	srand(time(0));

	HWND hwnd = CreateWindow(className, "Space Invaders", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, createMenu(), hInstance, 0);

	UpdateWindow(hwnd);
	ShowWindow(hwnd, nShowCmd);

	InitializeGraphics(hwnd);
	/* initialize the game */
	InitializeGame(&g, hwnd);

	MSG msg = { 0 };
	BOOL isRunning = TRUE;
	while (isRunning) {
		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				isRunning = FALSE;
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			Sleep(10);
			/* updates all the components of the game */
			UpdateGame(&g);

		}
	}
	/* free memory */
	ShutDownGame(&g);
	ShutdownGraphics();
	return 0;
}