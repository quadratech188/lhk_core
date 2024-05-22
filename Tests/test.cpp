#include <iostream>
#include <stdexcept>
#include <windows.h>
#include "KeyboardHook.h"
#include "lua.hpp"

#include "pch.h"
#include "KeyboardSubHook.h"
#include "KeyboardStroke.h"
#include "LuaEnvironment.h"

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

namespace KeyboardStroke {
	class KeyboardStrokeTest: public testing::Test {
	protected:
		lua_State* L;
		KeyboardStrokeTest() {
			L = luaL_newstate();
			luaL_openlibs(L);
			KeyboardStroke::open(L);
			lua_register(L, "debugPrint", Utils::debugPrint);
		}
	};
	
	TEST_F(KeyboardStrokeTest, SanityCheck) {
		Utils::runText(L, R"ESCAPESEQUENCE(
k = KeyStroke.new(24, nil, true)

if (k.vkCode ~= 24) then
	print("Incorrect vkCode: expected 24, got " .. k.vkCode)
	return
end

if (k.stroke ~= true) then
	print("Incorrect stroke: expected true, got " .. k.stroke)
	return
end

debugPrint("Test Successful")
		)ESCAPESEQUENCE");
		EXPECT_EQ(Utils::lastMessage, std::string("Test Successful"));
	}
}

namespace KeyboardSubHook {
	class KeyboardHookTest : public testing::Test {
	protected:
		lua_State* L;
		KeyboardHookTest() {
			L = luaL_newstate();
			luaL_openlibs(L);
			KeyboardSubHook::open(L);
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

namespace HookCallbackTest {
	class KeyboardTest: public testing::Test {
	protected:
		
		KBDLLHOOKSTRUCT spoofedHookInfo = KBDLLHOOKSTRUCT {123, 456, 1, 78, NULL};

		KeyboardTest() {
			LuaEnv::init();
			KeyboardSubHook::open(LuaEnv::L);
		}
	};

	TEST_F(KeyboardTest, SanityCheck) {
		Utils::runText(LuaEnv::L, R"ESCAPESEQUENCE(
k = KeyboardSubHook.new()
k.callback = function(keyStroke) debugPrint(tostring(keyStroke)) return end
		)ESCAPESEQUENCE");

		KeyboardHook::hookProc(0, WM_KEYDOWN, (LPARAM)&spoofedHookInfo);

		EXPECT_EQ(Utils::lastMessage, std::string("123"));
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
