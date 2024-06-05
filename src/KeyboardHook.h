#pragma once

#include <windows.h>
#include <winuser.h>

namespace KeyboardHook {
	bool hook();

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
}
