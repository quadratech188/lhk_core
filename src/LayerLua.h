#include <string>

#include "LuaHeader.h"

namespace LayerLua {
	struct LayerUserdata {
		std::string name;
	};
	
	void open(lua_State* L);
	int newUserdata(lua_State* L);
	int get(lua_State* L);

	int index(lua_State* L);
	int activate(lua_State* L);
	int deactivate(lua_State* L);
	int reg(lua_State* L);
}
