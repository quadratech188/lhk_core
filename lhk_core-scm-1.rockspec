package = "lhk_core"
version = "scm-1"
source = {
	url = "git://github.com/quadratech188/lhk_core",
	branch = "main"
}
description = {
	summary = "C++ core for lhk",
	detailed = [[
	C++ core for lhk
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
			[''] = 'lib/lhk_core.dll'
		},
		lua = {
		}
	}
}
