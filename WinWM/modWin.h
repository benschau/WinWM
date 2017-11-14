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
#include <map>

namespace WinWM {
	enum Action {
		NEW_WINDOW = 1
	};

	class WM {
		private:
			std::vector<HWND> windows;

		public:
			BOOL WINAPI init();
			static BOOL WINAPI newWindow();

			INT resizeWindow();
	};

	VOID WINAPI execAction(WPARAM);
}

#endif 