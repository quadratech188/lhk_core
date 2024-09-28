#pragma once

#include <array>
#include "LuaHeader.h"
#include <variant>

#include "AttributeTree.h"
#include "KeyStroke.h"
#include "Flags.h"

namespace KeyboardSubHook {
	struct SubHook {
		std::variant<int, KeyStrokes> data;
		Flags flags;
		void run();
		SubHook(lua_State* L, int index);
		SubHook(std::variant<int, KeyStrokes> data, Flags flags): flags(flags), data(data) {};
	};
	
	extern AttributeTree<SubHook> subHooks;
	
	std::array<int, 5> getFilter(lua_State* L, int index);
	std::variant<int, KeyStrokes> getActions(lua_State* L, int index);
}
