// SendMessage.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>



struct  wxStr
{
	wchar_t * pStr;
	int strLen;
	int strLen2;

};

//��ȡģ���ַ
DWORD GetWeChatWin(){
	return (DWORD)LoadLibrary(L"WeChatWin.dll");
}

VOID SendTextMessage(wchar_t * wxid, wchar_t * message){


	//������Ϣcall
	DWORD sendCall = GetWeChatWin() + 0xCBE32;
	//��װ��Ҫ�����ݸ�ʽ
	wxStr pWxid = { 0 };
	pWxid.pStr = wxid;
	pWxid.strLen = wcslen(wxid);
	pWxid.strLen2 = wcslen(wxid)*2;

	wxStr pMessage = { 0 };
	pMessage.strLen = wcslen(message);
	pMessage.strLen2 = wcslen(message) * 2;

	char * asmWxid = (char *)&pWxid.pStr;
	char * asmMessage = (char *)&pMessage.pStr;
	char buff[0x81C] = { 0 };
	/*
        mov edx,dword ptr ss:[ebp-0x4C]          ; wxid
        lea eax,dword ptr ds:[edi+0x14]
        push 0x1
        push eax
        push edi                                 ; ����
        lea ecx,dword ptr ss:[ebp-0x880]
        call WeChatWi.1017BAA0
        add esp,0xC


	*/
	_asm{
		mov edx, asmWxid
		mov eax,0x0
		push 0x1
		push eax
		mov edi, asmMessage
		push edi
		lea ecx,buff
		call sendCall
		add esp, 0xC
	}
};