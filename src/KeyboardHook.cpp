#include <windows.h>
#include <stdio.h>
#include <list>

#include "KeyboardHookLua.h"
#include "KeyboardHook.h"

namespace KeyboardHook {
	bool hook() {
		SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, GetModuleHandle(NULL), 0);
		return true;
	}

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode < 0) {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}
		return 0;
	}
}
