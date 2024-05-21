#include <windows.h>
#include <stdio.h>
#include <winuser.h>

#include "KeyboardSubHook.h"
#include "KeyboardStroke.h"
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
		
		KBDLLHOOKSTRUCT strokeInfo = *(KBDLLHOOKSTRUCT*)lParam;
		
		KeyboardStroke::KeyStroke stroke;

		stroke.vkCode = strokeInfo.vkCode;
		stroke.scanCode = strokeInfo.scanCode;
				
		
		return 0;
	}

	
}
