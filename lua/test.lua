mylib, err = package.loadlib("bin/LuaHotKey.dll", "luaopen_LuaHotKey")

print(err)

mylib()

print(mylib)

print(lhk)

lhk.test()

for index, value in ipairs(lhk) do
	print(index)
end

for index, value in ipairs(lhk) do
	print(index)
end
