#include "KeyStroke.h"
#include "LuaHeader.h"

namespace KeyStrokeLua {
	void open(lua_State* L);
	KeyStroke get(lua_State* L, int index);
	int set(lua_State* L);
	int get(lua_State* L);
	int toString(lua_State* L);
	int newUserdata(lua_State* L);
	int newUserdata(lua_State* L, WPARAM wParam, LPARAM lParam);
	int newUserdata(lua_State* L, KeyStroke keyStroke);
}
