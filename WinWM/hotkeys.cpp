#include "stdafx.h"
#include "hotkeys.h"
#include "modWin.h"

/*
 * Read configuration file for WinWM. 
 * Assuming that file has a specific notation, mapping a set of keys to some functionality 
 *  of the program. See the example conf for more details.
 * @param path of the configuration file.
 * @return a boolean indicating success (true) or failure (false)
 */
BOOL WINAPI readConfig(std::string path) {
	
	return true;
}

/*
 * Reload the configuration file, assuming it is coming from the same path.
 * If you want to load a file from a different path, use readConfig();
 * @return a boolean indicating success (true) or failure (false)
 */
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

