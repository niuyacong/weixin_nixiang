// ReadAndWrite.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include <stdio.h>
#include "resource.h"
//��ȡwechatwin��ַ
DWORD getWechatWinadd(){
	HMODULE winAdd=LoadLibrary("WeChatWin.dll");
	return (DWORD)winAdd;
}

//��ȡ�ڴ�����
VOID readWeChatData(_In_ HWND hwndDilg){
	//�õ�ģ���ַ
	DWORD wechatWin = getWechatWinadd();

	//װ���ݵ�����
	CHAR wxiddata[0x100] = { 0 };
	sprintf_s(wxiddata, "%s", wechatWin + 0x10504B4);
	SetDlgItemText(hwndDilg, wxid, wxiddata);

	//΢���ǳ�
	CHAR nickname[0x100] = { 0 };
	sprintf_s(nickname, "%s", wechatWin + 0x105052C);
	SetDlgItemText(hwndDilg, wxnickname, nickname);


	//΢��ͷ�� ��ָ��
	//΢��ͷ���ַ��ȡ����
	/*CHAR headimg[0x100] = { 0 };
	DWORD pPic = wechatWin + 0x007C3E68;

	sprintf_s(headimg, "%s", (*(DWORD *)pPic));
	SetDlgItemText(hwndDilg, wxheadimg, headimg);*/
}

//д�ڴ�

//����  1�����д���ڴ棬΢��δ��Ӧ
VOID writeData(_In_ HWND hwndDilg){

	//OpenMutex
	//CreateMutexA
	//�õ�ģ���ַ
	DWORD wechatWin = getWechatWinadd();

	DWORD nickname = wechatWin + 0x10504B4;
	CHAR nickname_text[0x100] = { 0 };
	GetDlgItemText(hwndDilg, wxid, nickname_text, sizeof(nickname_text));
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)nickname, nickname_text, sizeof(nickname_text),NULL);
}