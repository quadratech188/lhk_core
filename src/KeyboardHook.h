#include <windows.h>

namespace Keyboard::KeyboardHook {
	bool hook();

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
}
