#include <lua.hpp>

#if defined(LUA_VERSION_NUM_) && LUA_VERSION_NUM < 502
	#define luaL_setfuncs(L, l, nup) luaL_register(L, NULL, l, nup)
	#define lua_rawlen(L, idx) lua_objlen(L, idx)
#endif
