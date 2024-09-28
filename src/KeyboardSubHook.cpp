#include "LuaHeader.h"
#include <array>
#include "KeyboardSubHook.h"
#include "Dll.h"
#include "KeyboardHook.h"
#include "Modifiers.h"
#include "Keyboard.h"
#include "Flags.h"
#include "KeyStrokeLua.h"
#include "LayerLua.h"

namespace KeyboardSubHook {
	AttributeTree<SubHook> subHooks;

	std::array<int, 5> getFilter(lua_State* L, int index) {
		luaL_argcheck(L, lua_istable(L, index), 1, NULL);
		lua_getfield(L, index, "vkCode");
		int vkCode = lua_isnumber(L, -1)? lua_tointeger(L, -1): 0;
		lua_pop(L, 1);
		lua_getfield(L, index, "scanCode");
		int scanCode = lua_isnumber(L, -1)? lua_tointeger(L, -1): 0;
		lua_pop(L, 1);
		lua_getfield(L, index, "stroke");
		int stroke = lua_isboolean(L, -1)? lua_toboolean(L, -1) + 1: 0; // 2 is up, 1 is down
		lua_pop(L, 1);
		lua_getfield(L, index, "autorepeated");
		int repeat = lua_isboolean(L, -1)? lua_toboolean(L, -1) + 1: 0; // 2 is when key is autorepeated (why would you want this), 
		lua_pop(L, 1);

		lua_getfield(L, index, "modifiers");
		int modifiers = Modifiers::createFromLua(L, -1);
		lua_pop(L, 1); // Pop 'modifiers' table

		return {vkCode, scanCode, modifiers, repeat, stroke};
	}

	std::variant<int, KeyStrokes> getActions(lua_State* L, int index) {
		if (lua_isfunction(L, index)) {
			lua_pushvalue(L, index); // Push function to the top of the stack
			return luaL_ref(L, LUA_REGISTRYINDEX); // Pop the function from the stack
		}
		else if (lua_istable(L, index)) {

			// Read keyStrokes table

			int length = lua_rawlen(L, index);
			KeyStroke* strokes = new KeyStroke[length];

			for (int i = 0; i < length; i++) {
				lua_rawgeti(L, index, i + 1); // lua indices start at 1
													  //
				// TODO: Better error message when the member is not a keystroke
				strokes[i] = KeyStrokeLua::get(L, -1); // Top element
				
				lua_pop(L, 1); // Pop top element
			}
			return KeyStrokes(strokes, length);
		}
		else {
			luaL_argcheck(L, 0, index, "Expected KeyStroke array or lua function");
		}
	}

	SubHook::SubHook(lua_State* L, int index) {
		this->data = getActions(L, index);
		if (lua_gettop(L) >= index + 1) {
			this->flags = Flags(L, index + 1);
		}
		else {
			this->flags = Flags();
		}
	}

	void SubHook::run() {
		if (std::holds_alternative<int>(this->data)) {
			lua_rawgeti(LuaHotKey::L, LUA_REGISTRYINDEX, std::get<int>(this->data));
			KeyStrokeLua::newUserdata(LuaHotKey::L, KeyboardHook::keyStroke);

			int err = lua_pcall(LuaHotKey::L, 1, 0, 0);

			if (err != 0) {
				std::cout << lua_tostring(LuaHotKey::L, -1) << std::endl;
			}
		}
		else if (std::holds_alternative<KeyStrokes>(this->data)) {
			KeyStrokes keyStrokes = std::get<KeyStrokes>(this->data);
			Keyboard::sendKeyStrokes(keyStrokes);
		}
		if (KeyboardHook::autoRepeat)
			KeyboardHook::block = this->flags.blockAutoRepeat;
		else
			KeyboardHook::block = this->flags.block;
	}
}
