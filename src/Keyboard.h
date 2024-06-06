#include <lua.hpp>

namespace Keyboard {
	void open(lua_State* L);
	int getKeyState(lua_State* L);
}
