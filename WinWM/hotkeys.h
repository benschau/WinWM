#ifndef HOTKEYS_H
#define HOTKEYS_H

#include "stdafx.h"
#include "modWin.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <WinUser.h>
#include <strsafe.h>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <queue>

namespace {
	struct fsKeys {
		static std::map<std::string, UINT> create_map() {
			std::map<std::string, UINT> m;
			m["ALT"] = 0x0001;
			m["CTRL"] = 0x0002;
			m["SHIFT"] = 0x0004;
			m["WIN"] = 0x0008;

			return m;
		};

		static const std::map<std::string, UINT> fsMods;
	};

	const std::map<std::string, UINT> fsKeys::fsMods = fsKeys::create_map();
}

const std::string DEFAULT_PATH = "winwm.conf";

typedef struct HotKey {
	std::vector<UINT> keyCombo;
	UINT vk = 0;
	UINT fsMod = 0;

	int (*action) ();
} HotKey; 

enum Action {
	NEW_WINDOW = 1
};

class Config {
	private:
		HANDLE hConfig;
		UINT super = 0x0008; // Default super key should be the windows key.
		std::string fpath = DEFAULT_PATH;
		std::vector<HotKey> keys;

	public:
		Config();
		Config(std::string path);

		BOOL WINAPI reload();
		
		BOOL WINAPI init();

		BOOL WINAPI registerKeys(std::queue<std::string> lines);
};

/*
 * Tools that I need to parse/act on hotkeys
 */
VOID WINAPI execAction(WPARAM);
std::vector<std::string> split(const std::string &s, char delim);

#endif
