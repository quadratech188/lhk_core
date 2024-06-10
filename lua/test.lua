Mylib, Err = package.loadlib("bin/LuaHotKey.dll", "luaopen_LuaHotKey")

print(Err)

Mylib()

print(Mylib)

print(lhk)

k = lhk.KeyboardSubHook.new()

k.callback = function (keyStroke)
	print(keyStroke.vkCode)
end

lhk.start()
