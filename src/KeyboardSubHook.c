#include <lua.h>
#include <lauxlib.h>
#include <string.h>

#include "KeyboardSubHook.h"
#include "Definitions.h"
#include "KeyboardHook.h"
#include "AttributeTree.h"

// Constants
static const char* userdataName = "lhk.KeyboardSubHook";
static const char* metatableName = "lhk.KeyboardSubHook";

static int new(lua_State* L);

static int set(lua_State* L);
static int get(lua_State* L);
static int block(lua_State* L);

AttributeTree<SubHook*> subHooks;

static const luaL_Reg luaFunctions[] = {
	{"new", new},
	{NULL, NULL}
};

static const luaL_Reg luaMembers[] = {
	{"__newindex", set},
	{"__index", get},
	{"block", block},
	{NULL, NULL}
};

void open(lua_State* L) {
	luaL_newmetatable(L, metatableName);
	luaL_openlib(L, NULL, luaMembers, 0);
	luaL_openlib(L, userdataName, luaFunctions, 0);
}

static int set(lua_State* L) {
	SubHook* keyboardSubHook = *LUA_CHECKUSERDATA(SubHook*, L, 1, metatableName);
	const char* index = luaL_checkstring(L, 2);

	if (!strcmp(index, "condition")) {
		lua_pushvalue(L, 3);
		keyboardSubHook->condition = luaL_ref(L, LUA_REGISTRYINDEX);
	}
	else if (!strcmp(index, "callback")) {
		lua_pushvalue(L, 3);
		keyboardSubHook->callback = luaL_ref(L, LUA_REGISTRYINDEX);
	}
	else {
		luaL_argcheck(L, 0, 2, "invalid index");
	}
	return 0;
}
static int get(lua_State* L) {
	SubHook* keyboardSubHook = *LUA_CHECKUSERDATA(SubHook*, L, 1, metatableName);
	const char* index = luaL_checkstring(L, 2);
	lua_pop(L, 0);
	if (!strcmp(index, "condition")) {
		lua_rawgeti(L, LUA_REGISTRYINDEX, keyboardSubHook->condition);
	}
	else if (!strcmp(index, "callback") {
		lua_rawgeti(L, LUA_REGISTRYINDEX, keyboardSubHook->callback);
	}
	else {
		luaL_argcheck(L, false, 2, "Invalid index");
	}
	return 1;
}
static int block(lua_State* L) {
	KeyboardHook_block(lua_gettop(L) == 1? lua_toboolean(L, 1): 1);
	return 0;
}

static int new(lua_State* L) {
	SubHook** userdataPtr = LUA_NEWUSERDATA(SubHook*, L);
	lua_pushvalue(L, 1);
	
	/*
	{
		vkCode
		scanCode
		stroke
	}
	*/
	lua_getfield(L, -1, "vkCode");
	int vkCode = lua_isnumber(L, -1)? lua_tointeger(L, -1): 0;
	lua_getfield(L, -1, "scanCode");
	int scanCode = lua_isnumber(L, -1)? lua_tointeger(L, -1): 0;
	lua_getfield(L, -1, "stroke");
	int stroke = lua_isboolean(L, -1)? lua_toboolean(L, -1) + 1: 0; // 2 is up, 1 is down

	lua_pushvalue(L, 2);

	subHooks.insert({vkCode, scanCode, stroke}, 3, luaL_ref(L, LUA_REGISTRYINDEX));

	luaL_getmetatable(L, metatableName);
	lua_setmetatable(L, -2);


	*userdataPtr = &subHooks.back();

	return 1;
}
