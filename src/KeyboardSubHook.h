#pragma once

#include <lauxlib.h>

#include "AttributeTree.h"

typedef struct {
	int callback;
} SubHook;

extern AttributeTree<int> subHooks;

void open(lua_State* L);
