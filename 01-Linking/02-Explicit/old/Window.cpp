#include <Windows.h>
#include "MyMath.h"

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
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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
	//variable declarations
	HMODULE hLib = NULL;
	typedef int (*PMAKESQUAREFUNCTION) (int);

	PMAKESQUAREFUNCTION pMakeSquare = NULL;

	int num1, num2;
	TCHAR str[255];

	//code
	switch (iMsg) {
	case WM_CREATE:
		hLib = LoadLibrary(TEXT("MyMath.dll"));

		if (hLib == NULL) {
			MessageBox(hwnd, TEXT("Load library failed"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd); // sends programatically WM_DESTROY to program
		}

		pMakeSquare = (PMAKESQUAREFUNCTION)GetProcAddress(hLib, "MakeSquare"); //MakeSquare = function name from header file MyMath.h
		
		if (pMakeSquare == NULL) {
			MessageBox(hwnd, TEXT("MakeSquare function address cannot be obtained"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}
		
		num1 = 15;
		num2 = pMakeSquare(num1);
		wsprintf(str, TEXT("Square of %d is %d"), num1, num2);
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		FreeLibrary(hLib);	//library load keli ahe tr swta free pn karun dyaychi OS la tras nahi dyaycha :)
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}