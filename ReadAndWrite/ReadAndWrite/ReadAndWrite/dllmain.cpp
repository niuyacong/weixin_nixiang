// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include "resource.h"
#include "ReadAndWrite.h"

INT_PTR CALLBACK Dlgproc(_In_ HWND hwndDilg, _In_ UINT uMsg, _In_  WPARAM wParam, _In_ LPARAM lParam);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DialogBox(hModule, MAKEINTRESOURCE(ID_MAIN), NULL, &Dlgproc);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


INT_PTR CALLBACK Dlgproc(_In_ HWND hwndDilg, _In_ UINT uMsg, _In_  WPARAM wParam, _In_ LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_INITDIALOG:
		readWeChatData(hwndDilg);
		break;
	case WM_COMMAND:
		if (wParam == read_data){
			readWeChatData(hwndDilg);
		}
		if (wParam == write_data){
			writeData(hwndDilg);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwndDilg,0);
		break;
	default:
		break;
	}
	return false;

}

