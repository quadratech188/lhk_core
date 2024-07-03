#pragma once

#include <windows.h>
#include <lua.h>
#include "Keyboard.h"

namespace Modifiers {
	int createFromLua(lua_State* L, int index);
	int createFromKeyboardState();
}

struct Flags {
	bool block: 1;
	bool blockAutoRepeat: 1;
	Flags(lua_State* L, int index);
	Flags();
};
