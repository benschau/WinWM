#include "stdafx.h"
#include "hotkeys.h"
#include "modWin.h"

WinWMConf::Config::Config() {
	this->init();
}

WinWMConf::Config::Config(std::string path) {
	this->fpath = path;
	if (!this->init()) {
		std::cout << "Couldn't initialize from configuration!" << std::endl;
	}
}

BOOL WINAPI WinWMConf::Config::reload() {
	if (init())
		return TRUE;

	return FALSE;
}

BOOL WINAPI WinWMConf::Config::init() {
	/*
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
	} */

	std::ifstream hFile(this->fpath);
	std::queue<std::string> lines;
	std::string line;
	while (std::getline(hFile, line)) {
		if (line == "" || line[0] == '#') // hashes will be our comments
			continue;	
		
		std::cout << line << std::endl;
		lines.push(line);
	}

	if (lines.empty()) {
		return false;
	} else {
		registerKeys(lines);
		return true;
	}
}

BOOL WINAPI WinWMConf::Config::registerKeys(std::queue<std::string> lines) {
	std::vector<std::string> hotkey_tokens, keystrokes;
	
	std::string defineSuper = lines.front();
	lines.pop();
	while (!lines.empty()) {
		HotKey *hk = new HotKey();
	
		hotkey_tokens = split(lines.front(), ' ');
		if (!hotkey_tokens.empty())
			keystrokes = split(hotkey_tokens[0], '+');
	
		for (std::string token : keystrokes) {
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
			} 
		}
		
		//hk->action = newWindow; // Just a test for now.
		hk->vk = VK_RETURN;
		hk->action = 1; // should be a random number, then map to a function in WM.
		
		if (!RegisterHotKey(NULL, hk->action, hk->fsMod | MOD_NOREPEAT, hk->vk)) {
			std::cout << "ERR (" << GetLastError() << "): Couldn't register the given hotkey." << std::endl;
			return false;
		} else {
			std::cout << "Hotkey registered." << std::endl;
		} 


		lines.pop();
		delete hk; 
	}
		
	/*
	if (!RegisterHotKey(NULL, 1, MOD_CONTROL | MOD_NOREPEAT, 0x42)) {
		std::cout << "ERR (" << GetLastError() << "): Couldn't register the given hotkey." << std::endl;
	} */

	return true;
}

std::vector<std::string> WinWMConf::split(const std::string &s, char delim) {
	std::istringstream buf(s);
	std::istream_iterator<std::string> begin(buf), end;
	std::vector<std::string> tokens(begin, end);

	return tokens;
}
