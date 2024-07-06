Mylib, Err = package.loadlib("bin/LuaHotKey.dll", "luaopen_LuaHotKey")

print(Err)

Mylib()

print(Mylib)


function printTable(t, indent)
    indent = indent or ""
    for k, v in pairs(t) do
        if type(v) == "table" then
            print(indent .. tostring(k) .. ":")
            printTable(v, indent .. "  ")
        else
            print(indent .. tostring(k) .. ": " .. tostring(v))
        end
    end
end

printTable(lhk)

a = lhk.keyStroke.new(0x57)
b = lhk.keyStroke.new(0x45)
print(a)

local data = {
	lhk.keyStroke.new(0x45),
	lhk.keyStroke.new(0x45, nil, true)
}

print(k)

local condition = {
	modifiers = {
	},
	autorepeated = true,
	vkCode = 0x54,
	stroke = false
}

-- lhk.keyboardSubHook.register(condition, data, {block = false, blockAutoRepeat = true})

-- lhk.start()
