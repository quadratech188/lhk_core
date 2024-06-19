#include <windows.h>

#include <winuser.h>

#include "KeyboardSubHook.h"
#include "KeyStroke.h"
#include "lua.h"
#include "KeyboardHook.h"
#include "Dll.h"

static int block;

int KeyboardHook_hook() {
	return SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, GetModuleHandle(NULL), 0);
}

void KeyboardHook_block(int bool) {
	block = bool;
}

static LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode < 0) {
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}

	block = 0;
	
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
