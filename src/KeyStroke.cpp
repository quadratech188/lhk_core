#include "KeyStroke.h"

KeyStroke::KeyStroke(): vkCode(0), scanCode(0), stroke(Stroke()) {};

KeyStroke::KeyStroke(WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT strokeInfo = *(KBDLLHOOKSTRUCT*)lParam;

	switch(wParam) {
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		this->stroke = Stroke::PRESS;
		break;
		
		case WM_KEYUP:
		case WM_SYSKEYUP:
		this->stroke = Stroke::RELEASE;
	}

	this->vkCode = strokeInfo.vkCode;
	this->scanCode = strokeInfo.scanCode;
}
