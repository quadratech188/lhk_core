
#pragma once
#include "lua.hpp"

#include "AttributeTree.h"

namespace KeyboardSubHook {

	struct SubHook {
		int callback;
	};
	
	extern AttributeTree<int> subHooks;

	void open(lua_State* L);
	int set(lua_State* L);
	int get(lua_State* L);
	int block(lua_State* L);
	int newUserdata(lua_State* L);
}
