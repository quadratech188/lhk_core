#include <iostream>
#include <stdexcept>
#include "lua.hpp"

#include "pch.h"
#include "KeyboardHookLua.h"

namespace Utils {
	const char* lastMessage;
	void runText(lua_State* L, const char* text) {
		int err = luaL_loadstring(L, text);
		if (err != 0) {
			throw std::runtime_error(lua_tostring(L, -1));
		}
		err = lua_pcall(L, 0, 0, 0);
		if (err != 0) {
			throw std::runtime_error(lua_tostring(L, -1));
		}
	}
	int debugPrint(lua_State* L) {
		const char* str = luaL_checkstring(L, 1);
		std::cout << str << std::endl;
		lastMessage = str;
		return 0;
	}
}
namespace KeyboardHook {
	class KeyboardHookTest : public testing::Test {
	protected:
		lua_State* L;
		KeyboardHookTest() {
			L = luaL_newstate();
			luaL_openlibs(L);
			KeyboardHook::open(L);
			lua_register(L, "debugPrint", Utils::debugPrint);
		}
	};

	TEST_F(KeyboardHookTest, SanityCheck) {
		Utils::runText(L, R"ESCAPESEQUENCE(
k = KeyboardSubHook.new()
k.condition = function() return "debugPrint" end
a = k.condition
debugPrint(a())
)ESCAPESEQUENCE");
		EXPECT_EQ(Utils::lastMessage, std::string("debugPrint"));
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
