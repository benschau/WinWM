#ifndef MODWIN_H
#define MODWIN_H

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <WinUser.h>
#include <strsafe.h>
#include <string>
#include <vector>

class WM {
	private:
		std::vector<HWND> windows;

	public:
		BOOL WINAPI init();

		VOID WINAPI newWindow();

		VOID WINAPI resizeWindow();
};

#endif 