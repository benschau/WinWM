#include "stdafx.h"
#include "hotkeys.h"
#include "modWin.h"

Config::Config() {
	this->init();
}

Config::Config(std::string path) {
	this->fpath = path;
	this->init();
}

BOOL WINAPI Config::reload() {
	return TRUE;
}

BOOL WINAPI Config::init() {
	this->hConfig = CreateFile((LPCWSTR) this->fpath.c_str(),
						 GENERIC_READ,
						 0,
						 NULL,
						 OPEN_EXISTING,
						 FILE_ATTRIBUTE_NORMAL,
						 NULL);

	if (this->hConfig == INVALID_HANDLE_VALUE) {
		std::cout << "ERR (" << GetLastError() << "): Couldn't open config." << std::endl;
	}
	
	LPVOID buff = 0;
	LPDWORD numBytes = 0;
	while (!ReadFile(this->hConfig, buff, 1, numBytes, NULL)) {
		std::cout << buff;
	}

	return true;
}

BOOL WINAPI Config::registerKeys() {
	if (!RegisterHotKey(NULL, TEST_FUNC, MOD_ALT | MOD_NOREPEAT, 0x42)) {
		std::cout << "ERR (" << GetLastError() << "): Couldn't register the given hotkey." << std::endl;
		return false;
	}

	return true;
}

/*
 * Execute the right action based on the given hotkey.
 *
 */
VOID WINAPI execAction(WPARAM wParam) {
	switch (wParam) {
		case TEST_FUNC:
			//testFunction();
			break;
		default:
			break;
	}
}

