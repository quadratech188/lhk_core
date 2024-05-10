#include "lua.hpp"

#include <string>

#include "KeyboardHookLua.h"
#include "Definitions.h"

namespace KeyboardHook {
	// Constants
	const char* userdataName = "KeyboardSubHook";
	const char* metatableName = "lhk.KeyboardSubHook";

	struct KeyboardSubHook {
		int condition; // Stored as lua references
		int callback;
	};

	SUBHOOKS subHooks;

	static const luaL_Reg luaFunctions[] = {
		*new luaL_Reg {"new", newUserdata}
	};

	static const luaL_Reg luaMembers[] = {
		{"__newindex", set},
		{"__index", get},
		{nullptr, nullptr}
	};
	
	void open(lua_State* L) {
		luaL_newmetatable(L, metatableName);
		luaL_openlib(L, NULL, luaMembers, 0);
		luaL_openlib(L, userdataName, luaFunctions, 0);
	}

	int set(lua_State* L) {
		KeyboardSubHook* keyboardSubHook = LUA_CHECKUSERDATA(KeyboardSubHook, L, 1, metatableName);
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
		KeyboardSubHook* keyboardSubHook = LUA_CHECKUSERDATA(KeyboardSubHook, L, 1, metatableName);
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
	
	int newUserdata(lua_State* L) {
		KeyboardSubHook* userdataPtr = LUA_NEWUSERDATA(KeyboardSubHook, L);
		lua_pushvalue(L, 1);
		userdataPtr->condition = luaL_ref(L, LUA_REGISTRYINDEX);

		lua_pushvalue(L, 2);
		userdataPtr->callback = luaL_ref(L, LUA_REGISTRYINDEX);

		luaL_getmetatable(L, metatableName);
		lua_setmetatable(L, -2);
		return 1;
	}
}
