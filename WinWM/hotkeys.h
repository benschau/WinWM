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

typedef struct HotKey {
	std::vector<UINT> vkeyCombo;
	UINT actionid;
} HotKey; 

enum Action {
	TEST_FUNC = 1
};

BOOL WINAPI reloadConfig();

BOOL WINAPI readConfig(std::string);

BOOL WINAPI registerHotKeys();

VOID WINAPI execAction(WPARAM);

#endif
