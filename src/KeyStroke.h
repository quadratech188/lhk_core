#pragma once

#include <lauxlib.h>
#include <windows.h>

typedef int STROKE;
#define STROKEDOWN 0;
#define STROKEUP 1;

typedef struct {
	DWORD vkCode;
	DWORD scanCode;
	STROKE stroke;
} KeyStrokeUdata;

void KeyStroke_open(lua_State* L);
