#pragma once

#include "lua.hpp"
#include <variant>

#include "AttributeTree.h"
#include "KeyStroke.h"

namespace KeyboardSubHook {

	struct SubHook {
		std::variant<int, std::span<KeyStroke::KeyStrokeUdata>> data;
	};
	
	extern AttributeTree<SubHook> subHooks;

	void open(lua_State* L);
	int reg(lua_State* L);
	void run(SubHook& subHook);
}
