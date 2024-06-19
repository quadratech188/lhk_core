#include <lauxlib.h>

#include <windows.h>
#include <winuser.h>

#include "Keyboard.h"
#include "AttributeTree.h"

static const luaL_Reg luaFunctions[] = {
	{"getKeyState", Keyboard_getKeyState},
	{NULL, NULL}
};

void Keyboard_open(lua_State* L) {
	luaL_openlib(L, "lhk.Keyboard", luaFunctions, 0);
}

int Keyboard_getKeyState(lua_State* L) {
	SHORT keyState = GetKeyState(lua_tointeger(L, 1));
	lua_pushboolean(L, keyState & 0x8000);
	lua_pushboolean(L, keyState & 1);

	return 2;
}
