#include "LuaEnvironment.h"
#include <stdexcept>
#include <format>
#include "lauxlib.h"
#include "lua.hpp"

namespace LuaEnv {
	lua_State* L;

	void init() {
		L = luaL_newstate();
	}

	void runFile(const char* filename) {
		int err = luaL_loadfile(L, filename);
		if (err != 0) {
			throw std::invalid_argument(std::format("Lua Error: {}", lua_tostring(L, -1)));
		}
		err = lua_pcall(L, 0, 0, 0);
		if (err != 0) {
			throw std::invalid_argument(std::format("Lua Error: {}", lua_tostring(L, -1)));
		}
	}
}
