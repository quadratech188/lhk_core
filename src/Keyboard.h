#pragma once

#include <windows.h>
#include <lua.hpp>

namespace Keyboard {
	extern BYTE keyboardState[256];
	void open(lua_State* L);
	int getKeyState(lua_State* L);
	bool isOn(DWORD vkCode);
	void updateKeyboardState();
}
