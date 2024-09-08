#pragma once

#include "LuaHeader.h"
#include <variant>

#include "AttributeTree.h"
#include "KeyStroke.h"
#include "Flags.h"

namespace KeyboardSubHook {
	struct SubHook {
		std::variant<int, KeyStrokes> data;
		Flags flags;
	};
	
	extern AttributeTree<SubHook> subHooks;

	void open(lua_State* L);
	int reg(lua_State* L);
	void run(SubHook& subHook);
}
