#include <lua.hpp>

#include <windows.h>
#include <winuser.h>

#include "Keyboard.h"
#include "KeyboardHook.h"
#include "KeyStroke.h"

namespace Keyboard {
	BYTE keyboardState[256];

	const luaL_Reg luaFunctions[] = {
		{"getKeyState", getKeyState},
		{NULL, NULL}
	};
	
	void open(lua_State* L) {
		luaL_openlib(L, "lhk.Keyboard", luaFunctions, 0);
	}

	int getKeyState(lua_State* L) {
		SHORT keyState = keyboardState[lua_tointeger(L, 1)];
		lua_pushboolean(L, keyState & 0x80);
		lua_pushboolean(L, keyState & 1);

		return 2;
	}
	bool isOn(DWORD vkCode) {
		// If we're currently handling the keypress, say that it's pressed. We're assuming that we 'just pressed shift' or 'didn't release shift yet'. This makes sense for most hotkeys.
		if (vkCode == KeyboardHook::keyStroke.vkCode) return true;

		SHORT keyState = GetKeyState(vkCode);
		return keyState & 0x80;
	}
}
