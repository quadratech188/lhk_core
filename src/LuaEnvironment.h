#pragma once

#include <stdexcept>
#include <format>
#include "lua.hpp"

namespace LuaEnv {
	void runFile(lua_State* L, const char* filename);
}
