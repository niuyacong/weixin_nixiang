// QR_CODE.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "QR_CODE.h"
#include <Windows.h>
#include "resource.h"
#include <TlHelp32.h>
#include <stdio.h>
#include "hook.h"
INT_PTR CALLBACK Dlgproc(_In_ HWND hwndDilg, _In_ UINT uMsg, _In_  WPARAM wParam, _In_ LPARAM lParam);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(MAIN), NULL, &Dlgproc);
	return 0;
}

INT_PTR CALLBACK Dlgproc(_In_ HWND hwndDilg, _In_ UINT uMsg, _In_  WPARAM wParam, _In_ LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		break;
	case WM_CLOSE:
		EndDialog(hwndDilg, 0);
		break;
	case WM_COMMAND:
		if (wParam == HOOK){
			//hook开始
		}
		if (wParam == UNHOOK){

		}
		break;
	default:
		break;
	}
	
	return FALSE;
}



