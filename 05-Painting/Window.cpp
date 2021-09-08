#include <Windows.h>

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
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//STEP 2: Register class
	RegisterClassEx(&wndclass);

	//create the window in memory
	hwnd = CreateWindow(
		szAppName,
		TEXT("GAP : My First Window"),
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
	//variable declaration
	HDC hdc;
	RECT rc;
	PAINTSTRUCT ps;
	HBRUSH hbrush;
	static int iPaintFlag = 0;

	//code
	switch (iMsg) {
	case WM_CHAR:
		switch (LOWORD(wParam)) {
		case 'R':
		case 'r':
			iPaintFlag = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'G':
		case 'g':
			iPaintFlag = 2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'B':
		case 'b':
			iPaintFlag = 3;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'C':
		case 'c':
			iPaintFlag = 4;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'M':
		case 'm':
			iPaintFlag = 5;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'Y':
		case 'y':
			iPaintFlag = 6;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'K':
		case 'k':
			iPaintFlag = 7;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case 'W':
		case 'w':
			iPaintFlag = 8;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
			
		case 'O':
		case 'o':
			iPaintFlag = 9;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		default:
			iPaintFlag = 0; // to make everything back if any other key is pressed
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		if (iPaintFlag == 1)
			hbrush = CreateSolidBrush(RGB(255, 0, 0));
		else if (iPaintFlag == 2)
			hbrush = CreateSolidBrush(RGB(0, 255, 0));
		else if (iPaintFlag == 3)
			hbrush = CreateSolidBrush(RGB(0, 0, 255));
		else if (iPaintFlag == 4)
			hbrush = CreateSolidBrush(RGB(0, 255, 255));
		else if (iPaintFlag == 5)
			hbrush = CreateSolidBrush(RGB(255, 0, 255));
		else if (iPaintFlag == 6)
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
		else if (iPaintFlag == 7)
			hbrush = CreateSolidBrush(RGB(0, 0, 0));
		else if (iPaintFlag == 8)
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
		else if (iPaintFlag == 9)
			hbrush = CreateSolidBrush(RGB(255, 165, 0));
		else
			hbrush = CreateSolidBrush(RGB(0, 0, 0));

		SelectObject(hdc, hbrush);
		FillRect(hdc, &rc, hbrush);
		DeleteObject(hbrush);

		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}