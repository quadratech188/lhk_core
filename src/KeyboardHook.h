#pragma once

#include <windows.h>
#include <winuser.h>

namespace KeyboardHook {
	extern bool block;

	bool hook();

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
}
