#include "stdafx.h"
#include "modWin.h"

using namespace WinWM;

BOOL WINAPI WM::init() {

	while (true) {
	}
	
	return true;
}

BOOL WINAPI WM::newWindow() {
	std::cout << "NEW WINDOW" << std::endl;

	return 0;
}

INT WM::resizeWindow() {
	return 0;
}

/*
 * Execute the right action based on the given hotkey.
 */
VOID WINAPI execAction(WPARAM wParam) {
	switch (wParam) {
		case NEW_WINDOW:
			WM::newWindow();
			break;
		default:
			break;
	}
}


