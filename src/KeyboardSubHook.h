#pragma once

#include "lua.hpp"

#include "AttributeTree.h"

namespace KeyboardSubHook {

	struct SubHook {
		int callback;
	};
	
	extern AttributeTree<SubHook> subHooks;

	void open(lua_State* L);
	int reg(lua_State* L);
	void run(SubHook& subHook);
}
