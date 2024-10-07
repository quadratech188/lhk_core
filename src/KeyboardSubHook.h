#pragma once

#include <array>
#include <optional>
#include <variant>

#include "AttributeTree.h"
#include "Flags.h"
#include "KeyStroke.h"
#include "LuaHeader.h"

namespace KeyboardSubHook {
	struct SubHook {
		std::variant<int, KeyStrokes> data;
		Flags flags;
		void run();
		SubHook(): data(0), flags(Flags()) {};
		SubHook(lua_State* L, int index);
		SubHook(std::variant<int, KeyStrokes> data, Flags flags): flags(flags), data(data) {};
	};
	
	extern AttributeTree<SubHook> subHooks;
	
	std::array<std::optional<int>, 5> getFilter(lua_State* L, int index);
	std::variant<int, KeyStrokes> getActions(lua_State* L, int index);
}
