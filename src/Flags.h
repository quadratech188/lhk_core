#pragma once

#include <lua.hpp>

struct Flags {
	bool block: 1;
	bool blockAutoRepeat: 1;
	Flags(lua_State* L, int index);
	Flags();
};
