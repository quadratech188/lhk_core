#include "lua.hpp"

#define SUBHOOKS std::list<KeyboardSubHook>

namespace KeyboardHook {
	struct KeyboardSubHook;

	void open(lua_State* L);
	int setCondition(lua_State* L);
	int setCallback(lua_State* L);
	int newUserdata(lua_State* L);
}
