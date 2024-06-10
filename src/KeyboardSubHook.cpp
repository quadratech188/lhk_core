#include "lua.hpp"

#include <string>
#include <list>

#include "KeyboardSubHook.h"
#include "Definitions.h"
#include "KeyboardHook.h"

namespace KeyboardSubHook {
	// Constants
	const char* userdataName = "lhk.KeyboardSubHook";
	const char* metatableName = "lhk.KeyboardSubHook";

	std::list<SubHook> subHooks;

	const luaL_Reg luaFunctions[] = {
		{"new", newUserdata},
		{NULL, NULL}
	};

	const luaL_Reg luaMembers[] = {
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

	int set(lua_State* L) {
		SubHook* keyboardSubHook = *LUA_CHECKUSERDATA(SubHook*, L, 1, metatableName);
		const char* index = luaL_checkstring(L, 2);

		if (index == std::string("condition")) {
			lua_pushvalue(L, 3);
			keyboardSubHook->condition = luaL_ref(L, LUA_REGISTRYINDEX);
		}
		else if (index == std::string("callback")) {
			lua_pushvalue(L, 3);
			keyboardSubHook->callback = luaL_ref(L, LUA_REGISTRYINDEX);
		}
		else {
			luaL_argcheck(L, false, 2, "invalid index");
		}
		return 0;
	}
	int get(lua_State* L) {
		SubHook* keyboardSubHook = *LUA_CHECKUSERDATA(SubHook*, L, 1, metatableName);
		const char* index = luaL_checkstring(L, 2);
		lua_pop(L, 0);
		if (index == std::string("condition")) {
			lua_rawgeti(L, LUA_REGISTRYINDEX, keyboardSubHook->condition);
		}
		else if (index == std::string("callback")) {
			lua_rawgeti(L, LUA_REGISTRYINDEX, keyboardSubHook->callback);
		}
		else {
			luaL_argcheck(L, false, 2, "Invalid index");
		}
		return 1;
	}
	int block(lua_State* L) {
		KeyboardHook::block = lua_gettop(L) == 1? lua_toboolean(L, 1): true;
		return 0;
	}
	
	int newUserdata(lua_State* L) {
		SubHook** userdataPtr = LUA_NEWUSERDATA(SubHook*, L);
		lua_pushvalue(L, 1);
	
		SubHook subHook;
		subHook.condition = luaL_ref(L, LUA_REGISTRYINDEX);

		lua_pushvalue(L, 2);
		subHook.callback = luaL_ref(L, LUA_REGISTRYINDEX);

		luaL_getmetatable(L, metatableName);
		lua_setmetatable(L, -2);

		subHooks.push_back(subHook);

		*userdataPtr = &subHooks.back();

		return 1;
	}
}
