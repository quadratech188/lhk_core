#include "LuaHeader.h"
#include <windows.h>

#include "Dll.h"
#include "KeyboardHook.h"
#include "KeyboardSubHook.h"
#include "KeyStrokeLua.h"
#include "Keyboard.h"

extern "C" __declspec(dllexport) int luaopen_LuaHotKey(lua_State* L) {
	LuaHotKey::open(L); // Creates the module

	KeyboardSubHook::open(L);
	KeyStrokeLua::open(L);
	Keyboard::open(L);
	return 1;
}

namespace LuaHotKey {
	lua_State* L;

	const luaL_Reg luaFunctions[] = {
		{"start", start},
		{NULL, NULL}
	};

	void open(lua_State* L) {
		LuaHotKey::L = L;
		lua_newtable(L);
		luaL_setfuncs(L, luaFunctions, 0);
	}

	int start(lua_State* L) {
		KeyboardHook::hook();

		MSG msg;
		while(GetMessage(&msg, NULL, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return 0;
	}
}
