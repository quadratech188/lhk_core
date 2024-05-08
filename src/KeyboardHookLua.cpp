#include "lua.hpp"

#include <list>

#include "KeyboardHookLua.h"
#include "Definitions.h"

namespace KeyboardHook {
	// Constants
	const char* userdataName = "KeyboardSubHook";
	const char* metatableName = "lhk.KeyboardSubHook";

	struct KeyboardSubHook {
		lua_CFunction condition;
		lua_CFunction callback;
	};

	SUBHOOKS subHooks;

	luaL_Reg luaFunctions[] = {
		*new luaL_Reg {"new", newUserdata}
	};

	luaL_Reg luaMembers[] = {
		*new luaL_Reg {"setCondition", setCondition},
		*new luaL_Reg {"setCallback", setCallback}
	};
	
	void open(lua_State* L) {
		luaL_newmetatable(L, userdataName);
		lua_pushstring(L, "__index");
		lua_pushvalue(L, -2);
		lua_settable(L, -3);
		luaL_openlib(L, NULL, luaMembers, 0);
		luaL_openlib(L, userdataName, luaFunctions, 0);
	}

	int setCondition(lua_State* L) {
		luaL_checkudata(L, 1, metatableName);
		KeyboardSubHook keyboardSubHook = *LUA_TOUSERDATA(SUBHOOKS::iterator, L, 1);
		lua_CFunction condition = lua_tocfunction(L, 2);
		keyboardSubHook.condition = condition;
		return 0;
	}

	int setCallback(lua_State* L) {
		luaL_checkudata(L, 1, metatableName);
		KeyboardSubHook keyboardSubHook = *LUA_TOUSERDATA(SUBHOOKS::iterator, L, 1);
		lua_CFunction callback = lua_tocfunction(L, 2);
		keyboardSubHook.callback = callback;
		return 0;
	}
	
	int newUserdata(lua_State* L) {
		KeyboardSubHook keyboardSubHook {
			NULL,
			NULL
		};
		subHooks.push_back(keyboardSubHook);
		SUBHOOKS::iterator iter = LUA_NEWUSERDATA(SUBHOOKS::iterator, L);

		iter = subHooks.end();
		return 0;
	}
}
