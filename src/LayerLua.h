#include <string>

#include "LuaHeader.h"

namespace LayerLua {
	struct LayerUserdata {
		std::string name;
		bool activated;
	};
	
	void open(lua_State* L);
	int newUserdata(lua_State* L);
	int get(lua_State* L);

	int getName(lua_State* L);
	int getActivated(lua_State* L);
	int activate(lua_State* L);
	int deactivate(lua_State* L);
	int reg(lua_State* L);
}
