#include <windows.h>

#include "KeyboardSubHook.h"
#include "KeyStroke.h"
#include "KeyboardHook.h"
#include "Modifiers.h"
#include <iostream>

namespace KeyboardHook {
	bool block;
	bool autoRepeat;
	bool shouldProcess = true;
	KeyStroke keyStroke;
	KeyStroke prevKeyStroke;

	bool hook() {
		SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, GetModuleHandle(NULL), 0);
		return true;
	}

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode < 0 || shouldProcess == false) {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}

		block = false;

		keyStroke = KeyStroke(wParam, lParam);

		autoRepeat = prevKeyStroke == keyStroke;

		int indexArray[] = {(int)keyStroke.vkCode,
			                (int)keyStroke.scanCode,
			                Modifiers::createFromKeyboardState(),
							autoRepeat + 1,
							keyStroke.stroke + 1};

		KeyboardSubHook::subHooks.callIncludingDefault(indexArray, KeyboardSubHook::run);

		prevKeyStroke = keyStroke;

		if (block) {
			return -1;
		}
		else {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}
	}
}
