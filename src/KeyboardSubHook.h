#pragma once

#include "lua.hpp"
#include <variant>

#include "AttributeTree.h"
#include "KeyStroke.h"

namespace KeyboardSubHook {
	struct KeyStrokes {
		std::span<KeyStroke::KeyStrokeUdata> keyStrokes;
	};

	struct SubHook {
		std::variant<int, KeyStrokes> data;
		bool block;
	};
	
	extern AttributeTree<SubHook> subHooks;

	void open(lua_State* L);
	int reg(lua_State* L);
	void run(SubHook& subHook);
}
