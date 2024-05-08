#include "lua.hpp"
#include "pch.h"

#include "iostream"
#include "format"

#include "KeyboardHookLua.h"

namespace Utils {
	const char* lastPrintout;

	int debugPrint(lua_State* L) {
		lastPrintout = luaL_checkstring(L, 1);
		std::cout << lastPrintout << std::endl;
		return 0;
	}

	lua_State* newDebugState() {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		lua_register(L, "debugPrint", debugPrint);
		return L;
	}

	void runText(lua_State* L, const char* str) {
		int err = luaL_loadstring(L, str);
		if (err != 0) {
			throw std::invalid_argument(std::format("Lua Error: {}", lua_tostring(L, -1)));
		}
		err = lua_pcall(L, 0, 0, 0);
		if (err != 0) {
			throw std::invalid_argument(std::format("Lua Error: {}", lua_tostring(L, -1)));
		}
	}
}

TEST(asdf, asdf) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}