#include <windows.h>
#include <iostream>

#include "Definitions.h"
#include "KeyboardSubHook.h"
#include "KeyStroke.h"
#include "LuaEnvironment.h"
#include "lua.h"
#include "KeyboardHook.h"

using namespace KeyStroke;

namespace KeyboardHook {
	bool hook() {
		SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, GetModuleHandle(NULL), 0);
		return true;
	}

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode < 0) {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}
		
		KeyStrokeUdata keyStroke = KeyStrokeUdata(wParam, lParam);

		for (const auto& it: KeyboardSubHook::subHooks) {
			lua_rawgeti(LuaEnv::L, LUA_REGISTRYINDEX, it.callback);
			KeyStroke::newUserdata(LuaEnv::L, keyStroke);
			int err = lua_pcall(LuaEnv::L, 1, 0, 0);

			if (err != 0) {
				std::cout << lua_tostring(LuaEnv::L, -1) << std::endl;
			}
		}

		return 0;
	}
}
