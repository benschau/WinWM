// WinWM.cpp : 
//

#include "stdafx.h"
#include "hotkeys.h"
#include "modWin.h"

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <WinUser.h>
#include <strsafe.h>
#include <string>

LRESULT WINAPI LLKeyboardProc(int, WPARAM, LPARAM);
VOID WINAPI cleanExit();
std::string WINAPI decodeErr(DWORD);

HANDLE hFile;
BOOL bErrFlag = FALSE;
char buff[2];

int main(int argc, char **argv)
{
	HHOOK hhookSysMsg;
	hhookSysMsg = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC) LLKeyboardProc, 0, 0);
	
	hFile = CreateFile((LPCWSTR) L"winwm.log", 
						GENERIC_WRITE, 
						0, 
						NULL, 
						CREATE_ALWAYS, 
						FILE_ATTRIBUTE_NORMAL, 
						NULL);
	
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << "ERR (" << GetLastError() << "): Couldn't create the file." << std::endl;
	}

	// Config object will automatically initialize, i.e read config file and register all hotkeys specified.
	Config conf("winwm_example.conf");

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0)) {
		PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
		
		switch (msg.message) {
			case WM_HOTKEY:
				execAction(msg.wParam);
			default:
				continue;
		}
	} 

	CloseHandle(hFile);
	UnregisterHotKey(NULL, 1);
	UnhookWindowsHookEx(hhookSysMsg);

	return 0;
}

LRESULT CALLBACK LLKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	char buff[2];
	int ret;
	
	DWORD bytesWritten = 0;
	DWORD dwBytesWritten = 0;

	if (nCode == HC_ACTION) {
		switch (wParam) {
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
				BYTE keyboard_state[256] = { 0 };
				PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam;
				
				if (!GetKeyboardState(keyboard_state)) {
					// handle error
					std::cout << "ERR (" << GetLastError() << "): Couldn't get the current keyboard state." << std::endl;
				}

				ret = ToAscii(p->vkCode, p->scanCode, keyboard_state, (LPWORD) buff, 0);
				switch (ret) {
					case 1:
						std::cout << "Key press: " << buff[0] << std::endl;
						dwBytesWritten = 1;
						break;
					case 2:
						std::cout << "Key press: " << buff[0] << buff[1] << std::endl;
						dwBytesWritten = 2;
						break;
				} 
				
				/* Keylogger portion; write each decipherable keystroke to a file.
				bErrFlag = WriteFile(hFile, buff, dwBytesWritten, &bytesWritten, NULL);
				if (bErrFlag == FALSE) {
					std::cout << "ERR (" << GetLastError() << "): Couldn't write to file." << std::endl;
				} 
				*/
				
				wprintf(L"Keyboard code: %#010x\n\n", p->vkCode);

				break;
		}
	}

	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

VOID WINAPI cleanExit() {
	
}

std::string WINAPI decodeErr(DWORD errMsgID) {
	// TODO: Use FormatMessage() to decode errMsgID, where errMsgID is the error code from GetLastError()

	return std::string();
}
