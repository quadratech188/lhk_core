#include "Flags.h"

static bool boolFromLua(lua_State* L, const char* index, int tableIndex, bool defaultBool) {
	lua_getfield(L, tableIndex, index);
	if (!lua_isboolean(L, -1))
		return defaultBool;

	bool result = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return result;
}

Flags::Flags() {
	block = true;
	blockAutoRepeat = true;
}

Flags::Flags(lua_State* L, int index) {
	if (lua_isnil(L, index)) {
		block = true;
		blockAutoRepeat = true;
	}

	luaL_argcheck(L, lua_istable(L, 1), 1, NULL);

	this->block = boolFromLua(L, "block", index, true);
	this->blockAutoRepeat = boolFromLua(L, "blockAutoRepeat", index, this->block);
}

static bool boolFromLua(lua_State* L, const char* index, int tableIndex, bool defaultBool) {
	lua_getfield(L, tableIndex, index);
	if (!lua_isboolean(L, -1))
		return defaultBool;

	bool result = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return result;
}
