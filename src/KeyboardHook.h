#include <windows.h>
#include <stdio.h>
#include <list>

#include "KeyboardHookLua.h"

namespace KeyboardHook {
	bool hook();

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
}
