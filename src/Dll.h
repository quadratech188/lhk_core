#include <lua.hpp>

extern "C" __declspec(dllexport) int luaopen_LuaHotKey(lua_State* L);

namespace LuaHotKey {
	extern lua_State* L;

	void open(lua_State* L);

	int start(lua_State* L);
}
