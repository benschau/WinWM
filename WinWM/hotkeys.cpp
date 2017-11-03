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
	if (init())
		return TRUE;

	return FALSE;
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
		// TODO: Interpret GetLastError() as string.
		std::cout << "ERR (" << GetLastError() << "): Couldn't open config." << std::endl;
	} 

	std::ifstream hFile(fpath);
	std::queue<std::string> lines;
	std::string line;
	while (std::getline(hFile, line)) {
		if (line[0] == '#') // hashes will be our comments
			continue;	

		lines.push(line);
	}

	registerKeys(lines);

	return true;
}

BOOL WINAPI Config::registerKeys(std::queue<std::string> lines) {
	/*
	if (!RegisterHotKey(NULL, TEST_FUNC, MOD_ALT | MOD_NOREPEAT, 0x42)) {
		std::cout << "ERR (" << GetLastError() << "): Couldn't register the given hotkey." << std::endl;
		return false;
	} */
	
	std::vector<std::string> hotkey_tokens, keystrokes;
	
	std::string defineSuper = lines.front();
	lines.pop();
	while (!lines.empty()) {
		HotKey *hk = new HotKey();
	
		hotkey_tokens = split(lines.front(), ' ');
		if (!hotkey_tokens.empty())
			keystrokes = split(hotkey_tokens[0], '+');
	
		for (std::string token : keystrokes) {
			/*
			if (token.compare("SUPER")) {
				hk->fsMod |= MOD_WIN;
			} else {
				if (fsKeys::fsMods.find(token) != fsKeys::fsMods.end()) {
					hk->fsMod |= fsKeys::fsMods.find(token)->second;
				}
				else {
					SHORT vkScan = 0;
					if (token.length() == 1) {
						// Assuming that the next token is one character...
						vkScan = VkKeyScanEx(token[0], GetKeyboardLayout(0));
					}
					else {
						std::cout << "Detected invalid hotkey argument " << token << ", ignoring." << std::endl;
					}

					hk->vk |= vkScan;
				} 
			} */

			std::cout << token << std::endl;
		}
		
		std::cout << std::endl;
		
		/*
		hk->action = newWindow; // Just a test for now.

		if (!RegisterHotKey(NULL, hk->action(), hk->fsMod, hk->vk)) {
			std::cout << "ERR (" << GetLastError() << "): Couldn't register the given hotkey." << std::endl;
			return false;
		}

		lines.pop();

		delete hk; */

		lines.pop();
	}

	return true;
}

/*
 * Execute the right action based on the given hotkey.
 */
VOID WINAPI execAction(WPARAM wParam) {
	switch (wParam) {
		case NEW_WINDOW:
			newWindow();
			break;
		default:
			break;
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::istringstream buf(s);
	std::istream_iterator<std::string> begin(buf), end;
	std::vector<std::string> tokens(begin, end);

	return tokens;
}
