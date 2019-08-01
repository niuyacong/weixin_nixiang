// ReadAndWrite.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <stdio.h>
#include "resource.h"
//获取wechatwin基址
DWORD getWechatWinadd(){
	HMODULE winAdd=LoadLibrary("WeChatWin.dll");
	return (DWORD)winAdd;
}

//读取内存数据
VOID readWeChatData(_In_ HWND hwndDilg){
	//拿到模块基址
	DWORD wechatWin = getWechatWinadd();

	//装数据的容器
	CHAR wxiddata[0x100] = { 0 };
	sprintf_s(wxiddata, "%s", wechatWin + 0x10504B4);
	SetDlgItemText(hwndDilg, wxid, wxiddata);

	//微信昵称
	CHAR nickname[0x100] = { 0 };
	sprintf_s(nickname, "%s", wechatWin + 0x105052C);
	SetDlgItemText(hwndDilg, wxnickname, nickname);


	//微信头像 是指针
	//微信头像地址获取有误
	/*CHAR headimg[0x100] = { 0 };
	DWORD pPic = wechatWin + 0x007C3E68;

	sprintf_s(headimg, "%s", (*(DWORD *)pPic));
	SetDlgItemText(hwndDilg, wxheadimg, headimg);*/
}

//写内存

//问题  1、点击写入内存，微信未响应
VOID writeData(_In_ HWND hwndDilg){

	//OpenMutex
	//CreateMutexA
	//拿到模块基址
	DWORD wechatWin = getWechatWinadd();

	DWORD nickname = wechatWin + 0x10504B4;
	CHAR nickname_text[0x100] = { 0 };
	GetDlgItemText(hwndDilg, wxid, nickname_text, sizeof(nickname_text));
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)nickname, nickname_text, sizeof(nickname_text),NULL);
}