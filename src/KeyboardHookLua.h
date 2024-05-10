#include "lua.hpp"

#include <list>

#include "Definitions.h"

#define SUBHOOKS std::list<KeyboardSubHook>

namespace KeyboardHook {
	struct KeyboardSubHook;

	void open(lua_State* L);
	int set(lua_State* L);
	int get(lua_State* L);
	int newUserdata(lua_State* L);
}
