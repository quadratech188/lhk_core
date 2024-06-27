Mylib, Err = package.loadlib("bin/LuaHotKey.dll", "luaopen_LuaHotKey")

print(Err)

Mylib()

print(Mylib)

print(lhk)

a = lhk.KeyStroke.new(0x57)
b = lhk.KeyStroke.new(0x45)
print(a)

local k = {
	lhk.KeyStroke.new(0xA2, nil, true),
	lhk.KeyStroke.new(0xA4, nil, true),
	lhk.KeyStroke.new(0x54, nil, true),
	lhk.KeyStroke.new(0x57),
	lhk.KeyStroke.new(0x45),
	lhk.KeyStroke.new(0x57, nil, true),
	lhk.KeyStroke.new(0x45, nil, true),
	lhk.KeyStroke.new(0xA2),
	lhk.KeyStroke.new(0xA4)
}

print(k)

local condition = {
	modifiers = {
		LCONTROL = true,
		LMENU = true
	},
	autorepeated = false,
	vkCode = 0x54,
	stroke = false
}

lhk.KeyboardSubHook.register(condition, k)

lhk.start()
