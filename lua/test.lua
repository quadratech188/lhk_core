Mylib, Err = package.loadlib("bin/LuaHotKey.dll", "luaopen_LuaHotKey")

print(Err)

Mylib()

print(Mylib)

print(lhk)

local k = function(t) print("hotkey") end

condition = {
	modifiers = {
		LCONTROL = true,
		LMENU = true
	},
	autorepeated = false,
	vkCode = 0x4B,
	stroke = false
}

lhk.KeyboardSubHook.register(condition, k)

lhk.start()
