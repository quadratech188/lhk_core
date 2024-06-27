#pragma once

#include <windows.h>

#include "KeyStroke.h"

namespace KeyboardHook {
	extern KeyStroke::KeyStrokeUdata keyStroke;
	extern bool block;
	extern int falseKeyStrokes;


	bool hook();

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
}
