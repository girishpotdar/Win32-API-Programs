#include <Windows.h>
#include "resource.h"

//Global function declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Global variable declaration

//Entry point function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyWindow");

	//code
	//STEP 1: Initialize WNDCLASSEX structure
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));

	//STEP 2: Register class
	RegisterClassEx(&wndclass);

	//create the window in memory
	hwnd = CreateWindow(
		szAppName,
		TEXT("ASTROMEDICOMP MATH SERVICES"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//Show window
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//STEP 3: Draw Heart of the application
	//Message loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//code
	PAINTSTRUCT ps;
	HDC hdc, hdcMem;
	HINSTANCE hInstance;
	static HBITMAP hBitmap;
	BITMAP bitmap;
	int x, y;
	static int cxClient, cyClient, cxSource, cySource;
	DWORD dw;

	switch (iMsg) {
	case WM_CREATE:
		//cxSource = GetSystemMetrics(SM_CXSIZEFRAME) + GetSystemMetrics(SM_CXSIZE);
		//cySource = GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYCAPTION);
		
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		//hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(MYBITMAP));
		hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
		//hBitmap = LoadBitmap(GetModuleHandle(NULL), TEXT("MYBITMAP"));
		//hBitmap = LoadBitmap(hInstance, TEXT("MYBITMAP"));
		//hBitmap = LoadBitmap(NULL, MAKEINTRESOURCE(MYBITMAP));
		//hBitmap = (HBITMAP)LoadImage(0, MAKEINTRESOURCE(MYBITMAP), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		//hBitmap = (HBITMAP)LoadImage(NULL, MAKEINTRESOURCE(MYBITMAP), IMAGE_BITMAP, 0, 0, 0);

		if (hBitmap == NULL)
		{
			MessageBox(hwnd, "Could not load MYBITMAP!", "Error", MB_OK);
			exit(0);
		}
		GetObject(hBitmap, sizeof(BITMAP), &bitmap);
		cxSource = bitmap.bmWidth;
		cySource = bitmap.bmHeight;
		break;

	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = LOWORD(lParam);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hdcMem = CreateCompatibleDC(hdc);
		SelectObject(hdcMem, hBitmap);
		StretchBlt(hdc, 0,0, cxClient, cyClient, hdcMem, 0, 0, cxSource, cySource, SRCCOPY);
		DeleteObject(hdc);
		ReleaseDC(hwnd, hdcMem);
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
