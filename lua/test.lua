mylib, err = package.loadlib("bin/LuaHotKey.dll", "luaopen_LuaHotKey")

print(err)

mylib()

print(mylib)

print(lhk)

k = lhk.KeyboardSubHook.new()

k.callback = function (keyStroke)
	print(keyStroke.vkCode)
end

lhk.start()
