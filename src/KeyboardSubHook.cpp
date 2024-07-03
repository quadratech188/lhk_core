#include "lua.hpp"
#include <span>
#include <iostream>

#include "KeyboardSubHook.h"
#include "Dll.h"
#include "KeyboardHook.h"
#include "Modifiers.h"
#include "Keyboard.h"
#include "Flags.h"
#include "KeyStrokeLua.h"

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

		luaL_argcheck(L, lua_istable(L, 1), 1, NULL);
		lua_getfield(L, 1, "vkCode");
		int vkCode = lua_isnumber(L, -1)? lua_tointeger(L, -1): 0;
		lua_pop(L, 1);
		lua_getfield(L, 1, "scanCode");
		int scanCode = lua_isnumber(L, -1)? lua_tointeger(L, -1): 0;
		lua_pop(L, 1);
		lua_getfield(L, 1, "stroke");
		int stroke = lua_isboolean(L, -1)? lua_toboolean(L, -1) + 1: 0; // 2 is up, 1 is down
		lua_pop(L, 1);
		lua_getfield(L, 1, "autorepeated");
		int repeat = lua_isboolean(L, -1)? lua_toboolean(L, -1) + 1: 0; // 2 is when key is autorepeated (why would you want this), 
																		// and 1 is when key is not autorepeated
		lua_pop(L, 1);


		lua_getfield(L, 1, "modifiers");

		int indexArray[] = {vkCode, scanCode, Modifiers::createFromLua(L, -1), repeat, stroke};

		lua_pop(L, 1); // Pop 'modifiers' table

		SubHook subHook;

		if (lua_isfunction(L, 2))
			subHook.data = luaL_ref(L, LUA_REGISTRYINDEX);
		else if (lua_istable(L, 2)) {


			// Read keyStrokes table

			int length = lua_objlen(L, 2);
			KeyStroke* strokes = new KeyStroke[length];

			for (int i = 0; i < length; i++) {
				lua_rawgeti(L, 2, i + 1); // lua indicies start at 1
				strokes[i] = KeyStrokeLua::get(L, -1);
				lua_pop(L, 1);
			}
			subHook.data = KeyStrokes(strokes, length);
		}

		else {
			luaL_argcheck(L, 0, 2, "Expected KeyStroke array or lua function");
		}
		
		subHook.flags = Flags(L, 3);

		// indexArray is a reference type, but it doesn't matter becuase AttributeTree.insert doesn't save a reference to the array.
		subHooks.insert(indexArray, subHook);

		return 0;
	}

	void run(SubHook& subHook) {

		if (std::holds_alternative<int>(subHook.data)) {
			lua_rawgeti(LuaHotKey::L, LUA_REGISTRYINDEX, std::get<int>(subHook.data));
			KeyStrokeLua::newUserdata(LuaHotKey::L, KeyboardHook::keyStroke);

			int err = lua_pcall(LuaHotKey::L, 1, 0, 0);

			if (err != 0) {
				std::cout << lua_tostring(LuaHotKey::L, -1) << std::endl;
			}
		}
		else if (std::holds_alternative<KeyStrokes>(subHook.data)) {
			KeyStrokes keyStrokes = std::get<KeyStrokes>(subHook.data);
			Keyboard::sendKeyStrokes(keyStrokes);
		}
		if (KeyboardHook::autoRepeat)
			KeyboardHook::block = subHook.flags.blockAutoRepeat;
		else
			KeyboardHook::block = subHook.flags.block;
	}
}
