#include <iostream>
#include <stdexcept>
#include <windows.h>
#include <winuser.h>
#include "lua.hpp"

#include "pch.h"
#include "Dll.h"
#include "KeyStroke.h"
#include "KeyboardHook.h"
#include "KeyboardSubHook.h"

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
	void hookProc(DWORD vkCode, DWORD scanCode, int stroke) {
		KBDLLHOOKSTRUCT hookInfo = {vkCode, scanCode, 0, 0, NULL};
		DWORD key = stroke != 0? WM_KEYUP: WM_KEYDOWN;
		KeyboardHook::hookProc(1, key, (LPARAM)&hookInfo);
	}
}

namespace KeyboardStroke {
	class KeyboardStrokeTest: public testing::Test {
	protected:
		lua_State* L;
		KeyboardStrokeTest() {
			L = luaL_newstate();
			luaL_openlibs(L);
			KeyStroke::open(L);
			lua_register(L, "debugPrint", Utils::debugPrint);
		}
	};
	
	TEST_F(KeyboardStrokeTest, SanityCheck) {
		Utils::runText(L, R"ESCAPESEQUENCE(
k = lhk.KeyStroke.new(24, nil, true)

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

namespace HookCallbackTest {
	class KeyboardSubHookTest: public testing::Test {
	protected:
		KBDLLHOOKSTRUCT spoofedHookInfo1 = KBDLLHOOKSTRUCT {123, 456, 78, 1, NULL};

		lua_State* L;

		KeyboardSubHookTest() {
			L = luaL_newstate();
			luaopen_LuaHotKey(L);
			luaL_openlibs(L);
			
			lua_register(L, "debugPrint", Utils::debugPrint);
			Utils::runText(LuaHotKey::L, R"ESCAPESEQUENCE(
callback = function(keyStroke) debugPrint(tostring(keyStroke.vkCode)) return end

data = {
	vkCode = nil,
	scanCode = 456,
	stroke = true
}

lhk.KeyboardSubHook.register(data, callback)
		)ESCAPESEQUENCE");
		}
	};

	TEST_F(KeyboardSubHookTest, SanityCheck) {
		Utils::hookProc(123, 456, 1);
		EXPECT_EQ(Utils::lastMessage, std::string("123"));
		Utils::lastMessage = "Blank";
		Utils::hookProc(234, 456, 0);
		EXPECT_EQ(Utils::lastMessage, "Blank");
		Utils::hookProc(345, 456, 1);
		EXPECT_EQ(Utils::lastMessage, std::string("345"));
	}
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
