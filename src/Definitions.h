#define LUA_NEWUSERDATA(T, L) *(T*)lua_newuserdata(L, sizeof(T))
#define LUA_TOUSERDATA(T, L, i) *(T*)lua_touserdata(L, i)

