#pragma once

#include <stdexcept>
#include <format>
#include "lua.hpp"

namespace LuaEnv {
	extern lua_State* L;

	void init();
	void runFile(const char* filename);
}
