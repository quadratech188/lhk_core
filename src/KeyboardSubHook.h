#pragma once

#include "lua.hpp"
#include <variant>

#include "AttributeTree.h"
#include "KeyStroke.h"
#include "Flags.h"

typedef std::span<KeyStroke::KeyStrokeUdata> KeyStrokes;

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
