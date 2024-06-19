#include <lualib.h>

__declspec(dllexport) int luaopen_LuaHotKey(lua_State* L);


void LuaHotKey_open(lua_State* L);

int LuaHotKey_start(lua_State* L);
