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

}

BOOL WINAPI Config::init() {

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
			testFunction();
			break;
		default:
			break;
	}
}

