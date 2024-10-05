#pragma once

#include <optional>
#include <windows.h>
#include <lua.h>
#include "Keyboard.h"

namespace Modifiers {
	std::optional<int> createFromLua(lua_State* L, int index);
	int createFromKeyboardState();
}
