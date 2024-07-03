#pragma once

#include <windows.h>

#include "KeyStroke.h"

namespace KeyboardHook {
	extern KeyStroke keyStroke;
	extern bool block;
	extern bool autoRepeat;
	extern bool shouldProcess;


	bool hook();

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
}
