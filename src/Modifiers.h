#pragma once

#include <windows.h>
#include <lua.h>
#include "Keyboard.h"

namespace Modifiers {
	int createFromLua(lua_State* L, int index);
	int createFromKeyboardState();
}
