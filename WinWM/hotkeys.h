#ifndef HOTKEYS_H
#define HOTKEYS_H

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <WinUser.h>
#include <strsafe.h>
#include <string>
#include <vector>

const std::string DEFAULT_PATH = "winwm.conf";

class Config {
	private:
		HANDLE hConfig;
		std::string fpath = DEFAULT_PATH;
		std::vector<HotKey> keys;

	public:
		Config();
		Config(std::string);

		BOOL WINAPI reload();
		
		BOOL WINAPI init();

		BOOL WINAPI registerKeys();
};


typedef struct HotKey {
	std::vector<UINT> vkeyCombo;
	UINT actionid;
} HotKey; 

enum Action {
	TEST_FUNC = 1
};

VOID WINAPI execAction(WPARAM);

#endif
