// wx.cpp : ����Ӧ�ó������ڵ㡣
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
	//�״μ���
	if (uMsg == WM_INITDIALOG){
		MessageBox(NULL, "�״μ���","����",0);
	}
	//�رհ�ť�¼�
	if (uMsg == WM_CLOSE){
		EndDialog(hwndDilg, 0);
	}
	//�������а�ť����¼�
	if (uMsg == WM_COMMAND){
		//ע�밴ť
		if (wParam == INDLL){
			InjectDll();
		}
		//ж�ذ�ť
		if (wParam == UNDLL){

		}
	}
	return FALSE;
}
//��һ��  �õ�΢�Ž��̾����ȥ����΢���ڴ�
//ͨ��΢�Ž�������ȥ�õ�΢��pid
DWORD ProcessNameFindPID(LPCSTR ProcessName){
	//1����ȡ����ϵͳ�Ľ��̿���
	//#include <TlHelp32.h>
	//�鿴����������ĵ���F1
	HANDLE  ProcessAll=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	//2���ڿ�������ͨ��ProcessName�ҵ�pid
	PROCESSENTRY32 processInfo = { 0 };
	processInfo.dwSize = sizeof(PROCESSENTRY32);
	
	do{
		if (strcmp(ProcessName, processInfo.szExeFile)==0){
			return processInfo.th32ProcessID;
		}
	} while (Process32Next(ProcessAll, &processInfo));
	return 0;
}


//�ڶ���  ��΢���ڲ�����һ���ڴ�������dll��·�� ��Ȼ��ͨ��pid��΢�Ž��̻�ý��̾��
VOID InjectDll(){
	CHAR pathStr[0x100] = {"D://1test//ReadAndWrite.dll"};//F://my//wx//ReadAndWrite//ReadAndWrite//Debug//ReadAndWrite.dll
	//1���Ȼ�ȡ΢�ž��
	DWORD PID = ProcessNameFindPID(WECHAT_PROCESS_NAME);
	if (PID == 0){
		MessageBox(NULL, "û���ҵ�΢�Ž��̻�΢��û������", "����",0);
		return;
	}
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (hProcess == NULL){
		MessageBox(NULL, "���̴�ʧ��", "����", 0);
		return;
	}
	//2�������ڴ�
	LPVOID  dllAdd=VirtualAllocEx(hProcess, NULL, sizeof(pathStr), MEM_COMMIT, PAGE_READWRITE);
	if (dllAdd == NULL){
		MessageBox(NULL, "�ڴ����ʧ��", "����", 0);
		return;
	}
	//3��д��dll�������ַ��
	if (WriteProcessMemory(hProcess, dllAdd, pathStr, sizeof(pathStr), NULL) == 0){
		MessageBox(NULL, "д���ڴ�ʧ��", "����", 0);
		return;
	}
	//����������  ��ʾ��д��ĵ�ַΪ��03BC0000 �õ������ַ��ce�鿴�����ַ�Ƿ���ֵ
	//CHAR test[0x100] = { 0 };
	//sprintf_s(test,"д��ĵ�ַΪ��%p",dllAdd);
	//OutputDebugString(test);
	HMODULE k32 = GetModuleHandle("Kernel32.dll");
	LPVOID loadAdd=GetProcAddress(k32, "LoadLibraryA");
	//LoadLibraryA()
	//ͨ��Զ���߳�  LoadLibraryW�����������ǵ�dll
	HANDLE exec=CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadAdd, dllAdd, 0, NULL);
	if (exec == NULL){
		MessageBox(NULL, "Զ��ע��ʧ��", "����", 0);
		return;
	}
}


