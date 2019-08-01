// wx.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "wx.h"
#include <Windows.h>
#include "resource.h"
#include <TlHelp32.h>
#include <stdio.h>


#define WECHAT_PROCESS_NAME "WeChat.exe"


INT_PTR CALLBACK Dlgproc(_In_ HWND hwndDilg, _In_ UINT uMsg, _In_  WPARAM wParam, _In_ LPARAM lParam);
VOID InjectDll();
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(ID_MAIN), NULL, &Dlgproc);
	return 0;
}
INT_PTR CALLBACK Dlgproc(_In_ HWND hwndDilg, _In_ UINT uMsg, _In_  WPARAM wParam, _In_ LPARAM lParam)
{
	//首次加载
	if (uMsg == WM_INITDIALOG){
		MessageBox(NULL, "首次加载","标题",0);
	}
	//关闭按钮事件
	if (uMsg == WM_CLOSE){
		EndDialog(hwndDilg, 0);
	}
	//界面所有按钮点击事件
	if (uMsg == WM_COMMAND){
		//注入按钮
		if (wParam == INDLL){
			InjectDll();
		}
		//卸载按钮
		if (wParam == UNDLL){

		}
	}
	return FALSE;
}
//第一步  拿到微信进程句柄，去操作微信内存
//通过微信进程名称去拿到微信pid
DWORD ProcessNameFindPID(LPCSTR ProcessName){
	//1、获取整个系统的进程快照
	//#include <TlHelp32.h>
	//查看方法的相关文档，F1
	HANDLE  ProcessAll=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	//2、在快照里面通过ProcessName找到pid
	PROCESSENTRY32 processInfo = { 0 };
	processInfo.dwSize = sizeof(PROCESSENTRY32);
	
	do{
		if (strcmp(ProcessName, processInfo.szExeFile)==0){
			return processInfo.th32ProcessID;
		}
	} while (Process32Next(ProcessAll, &processInfo));
	return 0;
}


//第二步  在微信内部申请一块内存用来放dll的路径 ，然后通过pid打开微信进程获得进程句柄
VOID InjectDll(){
	CHAR pathStr[0x100] = {"D://1test//ReadAndWrite.dll"};//F://my//wx//ReadAndWrite//ReadAndWrite//Debug//ReadAndWrite.dll
	//1、先获取微信句柄
	DWORD PID = ProcessNameFindPID(WECHAT_PROCESS_NAME);
	if (PID == 0){
		MessageBox(NULL, "没有找到微信进程或微信没有启动", "错误",0);
		return;
	}
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (hProcess == NULL){
		MessageBox(NULL, "进程打开失败", "错误", 0);
		return;
	}
	//2、申请内存
	LPVOID  dllAdd=VirtualAllocEx(hProcess, NULL, sizeof(pathStr), MEM_COMMIT, PAGE_READWRITE);
	if (dllAdd == NULL){
		MessageBox(NULL, "内存分配失败", "错误", 0);
		return;
	}
	//3、写入dll到这个地址中
	if (WriteProcessMemory(hProcess, dllAdd, pathStr, sizeof(pathStr), NULL) == 0){
		MessageBox(NULL, "写入内存失败", "错误", 0);
		return;
	}
	//会在输出面板  显示：写入的地址为：03BC0000 拿到这个地址用ce查看这个地址是否有值
	//CHAR test[0x100] = { 0 };
	//sprintf_s(test,"写入的地址为：%p",dllAdd);
	//OutputDebugString(test);
	HMODULE k32 = GetModuleHandle("Kernel32.dll");
	LPVOID loadAdd=GetProcAddress(k32, "LoadLibraryA");
	//LoadLibraryA()
	//通过远程线程  LoadLibraryW函数加载我们的dll
	HANDLE exec=CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadAdd, dllAdd, 0, NULL);
	if (exec == NULL){
		MessageBox(NULL, "远程注入失败", "错误", 0);
		return;
	}
}


