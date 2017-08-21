#include "stdafx.h"
#include "hotkeys.h"
#include "modWin.h"

/*
 * Generate template configuration file for WinWM.
 * @return a boolean indicating success (true) or failure (false)
 */
BOOL WINAPI generateConfig() {
	std::string path = DEFAULT_PATH;
	
	HANDLE hFile = CreateFile((LPCWSTR) path.c_str(), 
						GENERIC_WRITE, 
						0, 
						NULL, 
						CREATE_ALWAYS, 
						FILE_ATTRIBUTE_NORMAL, 
						NULL);

	return true;
}

/*
 * Generate template configuration file for WinWM.
 * @return a boolean indicating success (true) or failure (false)
 */
BOOL WINAPI readConfig(std::string path) {
	
	return true;
}

BOOL WINAPI reloadConfig() {
	
	return true;
}

BOOL WINAPI registerHotKeys() {
	// Read configuration file.	


	if (!RegisterHotKey(NULL, TEST_FUNC, MOD_ALT | MOD_NOREPEAT, 0x42)) {
		std::cout << "ERR (" << GetLastError() << "): Couldn't register the given hotkey." << std::endl;
		return false;
	}


	return true;
}

VOID WINAPI execAction(WPARAM wParam) {
	switch (wParam) {
		case TEST_FUNC:
			testFunction();
			break;
		default:
			break;
	}
}

