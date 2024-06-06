mylib, err = package.loadlib("bin/LuaHotKey.dll", "luaopen_LuaHotKey")

print(err)

mylib()

print(mylib)

print(lhk)

k = lhk.KeyboardSubHook.new()

local count = 0

k.callback = function (keyStroke)
	print(keyStroke.vkCode)
	print(lhk.Keyboard.getKeyState(0xA0))
end

lhk.start()
