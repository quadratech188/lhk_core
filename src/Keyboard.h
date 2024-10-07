#pragma once

#include <windows.h>

#include "KeyStroke.h"
#include "LuaHeader.h"

namespace Keyboard {
	extern BYTE keyboardState[256];
	void open(lua_State* L);
	int getKeyState(lua_State* L);
	bool isOn(DWORD vkCode);
	void updateKeyboardState();
	void sendKeyStrokes(KeyStrokes keyStrokes);
}
