#include <list>
#include <windows.h>

namespace KeyboardHook {
	bool hook();

	LRESULT CALLBACK hookProc(int nCode, WPARAM wParam, LPARAM lParam);
}
