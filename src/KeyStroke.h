#pragma once

#include <lua.hpp>
#include <windows.h>

typedef bool STROKE;
#define STROKEDOWN FALSE;
#define STROKEUP TRUE;

namespace KeyStroke {
	struct KeyStrokeUdata {
		DWORD vkCode;
		DWORD scanCode;
		STROKE stroke;
		KeyStrokeUdata(WPARAM, LPARAM);
		KeyStrokeUdata();
	};

	void open(lua_State* L);
	int set(lua_State* L);
	int get(lua_State* L);
	int newUserdata(lua_State* L);
	int newUserdata(lua_State* L, WPARAM wParam, LPARAM lParam);
	int newUserdata(lua_State* L, KeyStrokeUdata keyStroke);
}
