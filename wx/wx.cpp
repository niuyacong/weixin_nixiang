// wx.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "wx.h"
#include <Windows.h>
#include "resource.h"



#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

INT_PTR Dlgproc(HWND Arg1, UINT Arg2, WPARAM Arg3, LPARAM Arg4);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(ID_MAIN), NULL, &Dlgproc);
	return 0;
}
INT_PTR Dlgproc(HWND Arg1,UINT Arg2,WPARAM Arg3,LPARAM Arg4)
{
}



