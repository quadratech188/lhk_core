#include <windows.h>
#include <iostream>
#include <winuser.h>

#include "Definitions.h"
#include "KeyboardSubHook.h"
#include "KeyboardStroke.h"
#include "LuaEnvironment.h"
#include "lua.h"
#include "KeyboardHook.h"

using namespace KeyboardStroke;

namespace KeyboardHook {
	bool hook() {
		SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, GetModuleHandle(NULL), 0);
		return true;
	}

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode < 0) {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}
		
		KeyStroke keyStroke = KeyStroke(wParam, lParam);

		for (const auto& it: KeyboardSubHook::subHooks) {
			lua_pushvalue(LuaEnv::L, it.callback);
			*LUA_NEWUSERDATA(KeyStroke, LuaEnv::L) = keyStroke;
			int err = lua_pcall(LuaEnv::L, 1, 0, 0);
		}

		return 0;
	}

	
}
