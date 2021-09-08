#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	// code
	// dll injection / API hooking can be done with below cases :) 
	switch (dwReason) 
	{
	case DLL_PROCESS_ATTACH:
		break;

	case DLL_THREAD_ATTACH:
		break;

	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;

	default:
		break;

	}

	return TRUE;

}


//declaration specific --> decl spec --> __declspec keyword is Microsoft specific
extern "C" __declspec(dllexport) int MakeCube(int num)
{
	//code
	int cube = num * num * num;

	return cube;
}
