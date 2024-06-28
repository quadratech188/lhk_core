#include <lua.hpp>

#include <windows.h>
#include <span>
#include <stdexcept>
#include <string>

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

	void sendKeyStrokes(std::span<KeyStroke::KeyStrokeUdata> keyStrokes) {
		INPUT* inputs = (INPUT*)calloc(keyStrokes.size(), sizeof(INPUT));

		for (int i = 0; i < keyStrokes.size(); i++) {
			inputs[i].type = INPUT_KEYBOARD;
			if (keyStrokes[i].vkCode != 0) {
				inputs[i].ki.wVk = keyStrokes[i].vkCode;
			}
			else if (keyStrokes[i].scanCode != 0) {
				inputs[i].ki.wScan = keyStrokes[i].scanCode;
				inputs[i].ki.dwFlags += KEYEVENTF_SCANCODE;
			}
			
			if (keyStrokes[i].stroke == STROKEUP) {
				inputs[i].ki.dwFlags += KEYEVENTF_KEYUP;
			}
		}
		
		// Our hook is called again when we call SendInput. We don't want to process this, so we set shouldProcess to false when we call SendInput, and revert it after it is called.
		KeyboardHook::shouldProcess = false;
		int err = SendInput(keyStrokes.size(), inputs, sizeof(INPUT));
		KeyboardHook::shouldProcess = true;

		if (err != keyStrokes.size()) {
			throw std::runtime_error("SendInput failed: " + std::to_string(GetLastError()));
		}
	}
}
