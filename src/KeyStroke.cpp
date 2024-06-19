#include <windows.h>

#include <lauxlib.h>

#include "KeyStroke.h"
#include "Definitions.h"

static const char* userdataName = "lhk.KeyStroke";
static const char* metatableName = "lhk.KeyStroke";

static int new(lua_State* L);
static int set(lua_State* L);
static int get(lua_State* L);

static const luaL_Reg luaFunctions[] = {
	{"new", new},
	{NULL, NULL}
};

static const luaL_Reg luaMembers[] = {
	{"__newindex", set},
	{"__index", get},
	{NULL, NULL}
};

void KeyStroke_open(lua_State* L) {
	luaL_newmetatable(L, metatableName);
	luaL_openlib(L, NULL, luaMembers, 0);
	luaL_openlib(L, userdataName, luaFunctions, 0);
}

static int set(lua_State* L) {
	KeyStrokeUdata* keyStroke = LUA_CHECKUSERDATA(KeyStrokeUdata, L, 1, metatableName);
	const char* index = luaL_checkstring(L, 2);

	if (!strcmp(index, "vkCode")) {
		keyStroke->vkCode = lua_tointeger(L, 3);
	}
	else if (!strcmp(index, "scanCode")) {
		keyStroke->scanCode = lua_tointeger(L, 3);
	}
	else if (!strcmp(index, "stroke")) {
		keyStroke->stroke = lua_toboolean(L, 3);
	}
	else {
		luaL_argcheck(L, 0, 2, "invalid index");
	}
	return 0;
}


static int get(lua_State* L) {
	KeyStrokeUdata* keyStroke = LUA_CHECKUSERDATA(KeyStrokeUdata, L, 1, metatableName);
	const char* index = luaL_checkstring(L, 2);

	if (!strcmp(index, "vkCode")) {
		lua_pushinteger(L, keyStroke->vkCode);
	}
	else if (!strcmp(index, "scanCode")) {
		lua_pushinteger(L, keyStroke->scanCode);
	}
	else if (!strcmp(index, "stroke")) {
		lua_pushboolean(L, keyStroke->stroke);
	}
	else {
		luaL_argcheck(L, 0, 2, "invalid index");
	}
	return 1;
}

static int new(lua_State* L) {
	KeyStrokeUdata keyStroke;

	int numArgs = lua_gettop(L);
	
	keyStroke.vkCode = (numArgs >= 1 && !lua_isnil(L, 1))? lua_tointeger(L, 1): 0;

	keyStroke.scanCode = (numArgs >= 2 && !lua_isnil(L, 2))? lua_tointeger(L, 2): 0;

	keyStroke.stroke = numArgs >= 3? lua_toboolean(L, 3): STROKEDOWN;

	KeyStrokeUdata* userdataPtr = LUA_NEWUSERDATA(KeyStrokeUdata, L);

	*userdataPtr = keyStroke;

	luaL_getmetatable(L, metatableName);
	lua_setmetatable(L, -2);

	return 1;
}

int newWL(lua_State* L, WPARAM wParam, LPARAM lParam) {
	KeyStrokeUdata* userdataPtr = LUA_NEWUSERDATA(KeyStrokeUdata, L);

	*userdataPtr = KeyStrokeUdata(wParam, lParam);

	luaL_getmetatable(L, metatableName);
	lua_setmetatable(L, -2);

	return 1;

}

int newKS(lua_State* L, KeyStrokeUdata keyStroke) {
	*LUA_NEWUSERDATA(KeyStrokeUdata, L) = keyStroke;

	luaL_getmetatable(L, metatableName);
	lua_setmetatable(L, -2);

	return 1;
}

KeyStrokeUdata::KeyStrokeUdata(): vkCode(0), scanCode(0), stroke(FALSE) {};

KeyStrokeUdata::KeyStrokeUdata(WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT strokeInfo = *(KBDLLHOOKSTRUCT*)lParam;

	switch(wParam) {
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		this->stroke = STROKEDOWN;
		break;
		
		case WM_KEYUP:
		case WM_SYSKEYUP:
		this->stroke = STROKEUP;
	}

	this->vkCode = strokeInfo.vkCode;
	this->scanCode = strokeInfo.scanCode;
}
