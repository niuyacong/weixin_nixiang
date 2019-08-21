// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>
#include "resource.h"
#include "SendMessage.h"




DWORD ThreadPro(HMODULE hModule);
INT_PTR CALLBACK Dlgproc(_In_ HWND hwndDilg, _In_ UINT uMsg, _In_  WPARAM wParam, _In_ LPARAM lParam);
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		//启动一个线程初始化界面
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadPro, hModule, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

DWORD ThreadPro(HMODULE hModule){
	return DialogBox(hModule, MAKEINTRESOURCE(MAIN), NULL, Dlgproc);
}
INT_PTR CALLBACK Dlgproc(_In_ HWND hwndDilg, _In_ UINT uMsg, _In_  WPARAM wParam, _In_ LPARAM lParam){
	wchar_t wxid[0x100] = { 0 };
	wchar_t message[0x300] = { 0 };
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		if (wParam == ISOK){
			GetDlgItemText(hwndDilg, WXID, wxid, sizeof(wxid));
			GetDlgItemText(hwndDilg, WX_MESSAGE, message, sizeof(message));

			SendTextMessage(wxid,message);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwndDilg, 0);
		break;
	default:
		break;
	}
	return false;
};
