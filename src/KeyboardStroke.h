#pragma once

#include <lua.hpp>
#include <windows.h>

typedef bool STROKE;
#define STROKEDOWN FALSE;
#define STROKEUP TRUE;

namespace KeyboardStroke {
	struct KeyStroke {
		DWORD vkCode;
		DWORD scanCode;
		STROKE stroke;
		KeyStroke(WPARAM, LPARAM);
		KeyStroke();
	};

	void open(lua_State* L);
	int set(lua_State* L);
	int get(lua_State* L);
	int newUserdata(lua_State* L);
}
