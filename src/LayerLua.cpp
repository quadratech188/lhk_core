#include <array>
#include <optional>
#include <string>
#include <format>

#include "KeyboardSubHook.h"
#include "LuaHeader.h"

#include "LayerLua.h"

#include "Definitions.h"
#include "LuaHeader.h"
#include "Layers.h"

using namespace KeyboardSubHook;

namespace LayerLua {
	const char* metatableName = "lhk.Layer";

	const luaL_Reg luaFunctions[] = {
		{"new", newUserdata},
		{"get", get},
		{NULL, NULL}

	};
	
	const luaL_Reg luaMethods[] = {
		{"name", getName},
		{"activated", getActivated},
		{"activate", activate},
		{"deactivate", deactivate},
		{"register", reg},
		{NULL, NULL}
	};

	void open(lua_State* L) {
		lua_newtable(L);
		luaL_setfuncs(L, luaFunctions, 0);
		lua_setfield(L, -2, "Layer");

		luaL_newmetatable(L, metatableName);
		lua_pushvalue(L, -1); // Duplicate the metatable
		lua_setfield(L, -2, "__index"); // mt.__index = mt
		luaL_setfuncs(L, luaMethods, 0);
		lua_pop(L, 1); // Pop metatable
	}
	
	int newUserdata(lua_State* L) {

		std::string name = std::string(luaL_checkstring(L, 1));

		luaL_argcheck(L, !Layers::exists(name), 1, std::format("Layer {} already exists", name).c_str());

		Layers::newLayer(name);

		LayerUserdata* userdataPtr = LUA_NEWUSERDATA(LayerUserdata, L);

		new (userdataPtr) LayerUserdata {name, false};

		luaL_getmetatable(L, metatableName);
		lua_setmetatable(L, -2);

		return 1;
	}

	int get(lua_State* L) {
		std::string name = luaL_checkstring(L, 1);

		if (!Layers::exists(name)) {
			lua_pushnil(L);
			return 1;
		}

		LayerUserdata* userdataPtr = LUA_NEWUSERDATA(LayerUserdata, L);

		*userdataPtr = LayerUserdata {name};

		return 1;
	}

	int getName(lua_State* L) {
		LayerUserdata* layer = LUA_CHECKUSERDATA(LayerUserdata, L, 1, metatableName);
		lua_pushstring(L, layer->name.c_str());
		return 1;
	}

	int getActivated(lua_State* L) {
		LayerUserdata* layer = LUA_CHECKUSERDATA(LayerUserdata, L, 1, metatableName);
		lua_pushboolean(L, layer->activated);
		return 1;
	}


	int activate(lua_State* L) {
		LayerUserdata* layer = LUA_CHECKUSERDATA(LayerUserdata, L, 1, metatableName);

		if (!layer->activated) {
			Layers::activate(layer->name);
			layer->activated = true;
		}
		return 0;
	}
	int deactivate(lua_State* L) {
		LayerUserdata* layer = LUA_CHECKUSERDATA(LayerUserdata, L, 1, metatableName);

		if (layer->activated) {
			Layers::deactivate(layer->name);
			layer->activated = false;
		}
		return 0;
	}
	int reg(lua_State* L) {
		LayerUserdata* layerUserdata = LUA_CHECKUSERDATA(LayerUserdata, L, 1, metatableName);
		
		luaL_argcheck(L, Layers::exists(layerUserdata->name), 1, std::format("Layer '{}' does not exist", layerUserdata->name).c_str());

		auto layer = Layers::get(layerUserdata->name);

		std::array<std::optional<int>, 5> indexArray = KeyboardSubHook::getFilter(L, 2);

		SubHook subHook = SubHook(L, 3);

		layer->subHooks[indexArray] = subHook;

		return 0;
	}
}
