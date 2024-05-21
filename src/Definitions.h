#pragma once

#define LUA_NEWUSERDATA(type, L) (type*)lua_newuserdata(L, sizeof(type))
#define LUA_CHECKUSERDATA(type, L, index, typeName) (type*)luaL_checkudata(L, index, typeName)
