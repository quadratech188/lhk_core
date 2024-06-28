Mylib, Err = package.loadlib("bin/LuaHotKey.dll", "luaopen_LuaHotKey")

print(Err)

Mylib()

print(Mylib)

print(lhk)

a = lhk.KeyStroke.new(0x57)
b = lhk.KeyStroke.new(0x45)
print(a)

local data = {
	lhk.KeyStroke.new(0x45),
	lhk.KeyStroke.new(0x45, nil, true)
}

print(k)

local condition = {
	modifiers = {
	},
	autorepeated = nil,
	vkCode = 0x54,
	stroke = false
}

lhk.KeyboardSubHook.register(condition, nil, {block = true, autorepeat = false})

lhk.KeyboardSubHook.register(condition, data, {block = true, autorepeat = false})

lhk.start()
