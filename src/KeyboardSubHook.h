
#pragma once
#include "lua.hpp"

#include <list>

#include "Definitions.h"

namespace KeyboardSubHook {
	struct SubHook {
		int condition;
		int callback;
	};

	extern std::list<SubHook> subHooks;

	void open(lua_State* L);
	int set(lua_State* L);
	int get(lua_State* L);
	int block(lua_State* L);
	int newUserdata(lua_State* L);
}
