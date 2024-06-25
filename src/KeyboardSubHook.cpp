#include "lua.hpp"
#include <span>
#include <iostream>

#include "KeyboardSubHook.h"
#include "Dll.h"
#include "KeyStroke.h"
#include "KeyboardHook.h"
#include "AttributeTree.h"
#include "Modifiers.h"

namespace KeyboardSubHook {
	AttributeTree<SubHook> subHooks;

	const luaL_Reg luaFunctions[] = {
		{"register", reg},
		{NULL, NULL}
	};
	
	void open(lua_State* L) {
		luaL_openlib(L, "lhk.KeyboardSubHook", luaFunctions, 0);
	}
	
	int reg(lua_State* L) {
		SubHook subHook = {luaL_ref(L, LUA_REGISTRYINDEX)};

		luaL_argcheck(L, lua_istable(L, 1), 1, NULL);
		lua_getfield(L, -1, "vkCode");
		int vkCode = lua_isnumber(L, -1)? lua_tointeger(L, -1): 0;
		lua_pop(L, 1);
		lua_getfield(L, -1, "scanCode");
		int scanCode = lua_isnumber(L, -1)? lua_tointeger(L, -1): 0;
		lua_pop(L, 1);
		lua_getfield(L, -1, "stroke");
		int stroke = lua_isboolean(L, -1)? lua_toboolean(L, -1) + 1: 0; // 2 is up, 1 is down
		lua_pop(L, 1);

		lua_getfield(L, -1, "modifiers");

		int modifiers = Modifiers::createFromLua(L);

		int indexArray[] = {vkCode, scanCode, modifiers, stroke};

		// indexArray is a reference type, but it doesn't matter becuase AttributeTree.insert doesn't save a reference to the array.
		subHooks.insert(indexArray, subHook);

		return 0;
	}

	void run(SubHook& subHook) {
		lua_rawgeti(LuaHotKey::L, LUA_REGISTRYINDEX, subHook.callback);
		KeyStroke::newUserdata(LuaHotKey::L, KeyboardHook::keyStroke);
		int err = lua_pcall(LuaHotKey::L, 1, 0, 0);
		if (err != 0) {
			std::cout << lua_tostring(LuaHotKey::L, -1) << std::endl;
		}
	}
}
