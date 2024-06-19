#pragma once

#include <windows.h>
#include <winuser.h>


int KeyboardHook_hook();
void KeyboardHook_block(int bool);

static LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
