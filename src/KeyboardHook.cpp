#include <windows.h>

#include <winuser.h>

#include "KeyboardSubHook.h"
#include "KeyStroke.h"
#include "lua.h"
#include "KeyboardHook.h"
#include "Dll.h"

using namespace KeyStroke;

namespace KeyboardHook {
	bool block;

	bool hook() {
		SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, GetModuleHandle(NULL), 0);
		return true;
	}

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode < 0) {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}

		block = false;
		
		KeyStrokeUdata keyStroke = KeyStrokeUdata(wParam, lParam);

		for (const auto& it: KeyboardSubHook::subHooks) {
			lua_rawgeti(LuaHotKey::L, LUA_REGISTRYINDEX, it.callback);
			KeyStroke::newUserdata(LuaHotKey::L, keyStroke);
			int err = lua_pcall(LuaHotKey::L, 1, 0, 0);
		}
		if (block) {
			return 0;
		}
		else {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}
	}
}
