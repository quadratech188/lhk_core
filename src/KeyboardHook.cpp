#include <windows.h>
#include <winuser.h>

#include "lua.h"

#include "KeyboardSubHook.h"
#include "KeyStroke.h"
#include "Keyboard.h"
#include "KeyboardHook.h"
#include "Dll.h"
#include "Modifiers.h"

using namespace KeyStroke;

namespace KeyboardHook {
	bool block;
	KeyStrokeUdata keyStroke;

	bool hook() {
		SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, GetModuleHandle(NULL), 0);
		return true;
	}

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode < 0) {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}

		block = false;
		
		keyStroke = KeyStrokeUdata(wParam, lParam);

		int indexArray[] = {(int)keyStroke.vkCode,
			                (int)keyStroke.scanCode,
			                Modifiers::createFromKeyboardState(),
							keyStroke.stroke + 1};

		KeyboardSubHook::subHooks.callIncludingDefault(indexArray, KeyboardSubHook::run);

		if (block) {
			return 0;
		}
		else {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}
	}
}
