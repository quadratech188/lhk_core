#include <lualib.h>
#include <lauxlib.h>
#include <windows.h>

#include "Dll.h"
#include "KeyboardHook.h"
#include "KeyboardSubHook.h"
#include "KeyStroke.h"
#include "Keyboard.h"

__declspec(dllexport) int luaopen_LuaHotKey(lua_State* L) {
	KeyboardSubHook_open(L);
	KeyStroke_open(L);
	LuaHotKey_open(L);
	Keyboard_open(L);
	return 1;
}

static lua_State* luaState;

static const luaL_Reg luaFunctions[] = {
	{"start", LuaHotKey_start},
	{NULL, NULL}
};

void LuaHotKey_open(lua_State* L) {
	luaL_openlib(L, "lhk", luaFunctions, 0);
}

int LuaHotKey_start(lua_State* L) {
	luaState = L;

	if (!KeyboardHook_hook()) {
		//TODO
	}

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
