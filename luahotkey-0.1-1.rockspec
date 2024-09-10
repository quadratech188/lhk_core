package = "LuaHotKey"
version = "0.1-1"
source = {
	url = "git://github.com/quadratech188/LuaHotKey"
	tag = "v0.1"
}
description = {
	summary = "A Windows hotkey program as a lua module",
	detailed = [[
	TBD
	]],
	homepage = "",
	license = "MIT"
}
supported_platforms = {
	"windows",
	"win32",
	"cygwin"
}
dependencies = {
	"lua >= 5.1"
}

build = {
	variables = {
		LUA_LIBDIR = "$(LUA_LIBDIR)",
		LUA_INCDIR = "$(LUA_INCDIR)",
		LUA_LIBDIR_FILE = "$(LUA_LIBDIR_FILE)"
	},
	type = "cmake",

	install = {
		lib = {
			['lhk'] = 'lib/lhk_core.dll'
		}
	}
}
