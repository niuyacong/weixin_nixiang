#include "stdafx.h"
#define HOOK_LEN 5
DWORD getWeChatWin(){
	return (DWORD)LoadLibrary("WeChatWin.dll");
}

DWORD startHook(DWORD hookA,LPVOID funAdd){

	DWORD WeChatWin = getWeChatWin();
	DWORD hookAdd = WeChatWin + hookA;
	//要跳转的地址-hook的地址-5
	//组装数据byte
	BYTE jmpCode[HOOK_LEN] = { 0 };
	//jmpCode E9
	jmpCode[0] = 0XE9;
	//jmpCode = E9 2344555444
	*(DWORD *)&jmpCode[1] = (DWORD)funAdd - hookAdd - HOOK_LEN;

	//备份hook地址的数据
	ReadProcessMemory();
};