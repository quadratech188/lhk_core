#pragma once

#include <windows.h>
#include <stdio.h>
#include <winuser.h>

#include "KeyboardSubHook.h"
#include "KeyboardStroke.h"

namespace KeyboardHook {
	bool hook();

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
}
