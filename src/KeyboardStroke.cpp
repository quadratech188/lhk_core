#include <string>
#include <unordered_map>

#include <minwindef.h>
#include <windows.h>
#include <winuser.h>

#include <lua.hpp>

#include "KeyboardStroke.h"
#include "Definitions.h"
#include "lua.h"

namespace KeyboardStroke {
	const char* userdataName = "KeyStroke";
	const char* metatableName = "lhk.KeyStroke";

	const luaL_Reg luaFunctions[] = {
		{"new", newUserdata},
		{nullptr, nullptr}
	};

	const luaL_Reg luaMembers[] = {
		{"__newindex", set},
		{"__index", get},
		{nullptr, nullptr}
	};

	void open(lua_State* L) {
		luaL_newmetatable(L, metatableName);
		luaL_openlib(L, NULL, luaMembers, 0);
		luaL_openlib(L, userdataName, luaFunctions, 0);
	}

	int set(lua_State* L) {
		KeyStroke* keyStroke = LUA_CHECKUSERDATA(KeyStroke, L, 1, metatableName);
		std::string index = std::string(luaL_checkstring(L, 2));

		if (index == "vkCode") {
			keyStroke->vkCode = lua_tointeger(L, 3);
		}
		else if (index == "scanCode") {
			keyStroke->scanCode = lua_tointeger(L, 3);
		}
		else if (index == "stroke") {
			keyStroke->stroke = lua_toboolean(L, 3);
		}
		else {
			luaL_argcheck(L, false, 2, "invalid index");
		}
		return 0;
	}


	int get(lua_State* L) {
		KeyStroke* keyStroke = LUA_CHECKUSERDATA(KeyStroke, L, 1, metatableName);
		std::string index = std::string(luaL_checkstring(L, 2));

		if (index == "vkCode") {
			lua_pushinteger(L, keyStroke->vkCode);
		}
		else if (index == "scanCode") {
			lua_pushinteger(L, keyStroke->scanCode);
		}
		else if (index == "stroke") {
			lua_pushboolean(L, keyStroke->stroke);
		}
		else {
			luaL_argcheck(L, false, 2, "invalid index");
		}
		return 1;
	}

	int newUserdata(lua_State* L) {
		KeyStroke keyStroke;

		int numArgs = lua_gettop(L);
		
		keyStroke.vkCode = (numArgs >= 1 && !lua_isnil(L, 1))? lua_tointeger(L, 1): 0;

		keyStroke.scanCode = (numArgs >= 2 && !lua_isnil(L, 2))? lua_tointeger(L, 2): 0;

		keyStroke.stroke = numArgs >= 3? lua_toboolean(L, 3): STROKEDOWN;

		KeyStroke* userdataPtr = LUA_NEWUSERDATA(KeyStroke, L);

		*userdataPtr = keyStroke;

		luaL_getmetatable(L, metatableName);
		lua_setmetatable(L, -2);

		return 1;
	}

	KeyStroke::KeyStroke(): vkCode(0), scanCode(0), stroke(FALSE) {};

	KeyStroke::KeyStroke(WPARAM wParam, LPARAM lParam) {
		KBDLLHOOKSTRUCT strokeInfo = *(KBDLLHOOKSTRUCT*)lParam;

		KeyStroke keyStroke;
		switch(wParam) {
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			keyStroke.stroke = STROKEDOWN;
			break;
			
			case WM_KEYUP:
			case WM_SYSKEYUP:
			keyStroke.stroke = STROKEUP;
		}

		keyStroke.vkCode = strokeInfo.vkCode;
		keyStroke.scanCode = strokeInfo.scanCode;

	}
}
