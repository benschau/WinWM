#include "stdafx.h"
#include "hotkeys.h"
#include "modWin.h"

/*
 * Generate template configuration file for WinWM.
 * @return a boolean indicating success (true) or failure (false)
 */
BOOL WINAPI generateConfig() {

	std::string path;
	HANDLE hFile;
	BOOL bErrFlag;

	path = DEFAULT_PATH;
	hFile = CreateFile((LPCWSTR) path.c_str(), 
						GENERIC_WRITE, 
						0, 
						NULL, 
						CREATE_ALWAYS, 
						FILE_ATTRIBUTE_NORMAL, 
						NULL);
	
	bErrFlag = WriteFile(hFile, buff, dwBytesWritten, &bytesWritten, NULL);
	if (bErrFlag == FALSE) {
		std::cout << "ERR (" << GetLastError() << "): Couldn't write to file." << std::endl;
	}

	return true;
}

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

