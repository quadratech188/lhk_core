#include "KeyboardHook.h"

#include <windows.h>

#include "KeyStroke.h"
#include "KeyboardSubHook.h"
#include "Layers.h"
#include "Modifiers.h"

using namespace KeyboardSubHook;

namespace KeyboardHook {
	bool block;
	bool autoRepeat;
	bool shouldProcess = true;
	KeyStroke keyStroke;
	KeyStroke prevKeyStroke;

	bool hook() {
		SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, GetModuleHandle(NULL), 0);
		return true;
	}

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam) {
		if (nCode < 0 || shouldProcess == false) {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}

		block = false;

		keyStroke = KeyStroke(wParam, lParam);

		autoRepeat = prevKeyStroke == keyStroke;

		int indexArray[] = {(int)keyStroke.vkCode,
			                (int)keyStroke.scanCode,
			                Modifiers::createFromKeyboardState(),
							autoRepeat,
							(int)keyStroke.stroke};
			
		for (auto& layerIt: Layers::activatedLayers) {
			layerIt.second->second.subHooks.callIncludingDefault(indexArray, [](SubHook subHook) {subHook.run();});
		}

		prevKeyStroke = keyStroke;

		if (block) {
			return -1;
		}
		else {
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}
	}
}
