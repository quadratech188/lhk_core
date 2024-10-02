#pragma once

#include <windows.h>
#include <span>

#include "LuaHeader.h"
#include "Stroke.h"

struct KeyStroke {
	DWORD vkCode;
	DWORD scanCode;
	Stroke stroke;
	KeyStroke(WPARAM, LPARAM);
	KeyStroke();
	bool operator==(const KeyStroke& other) const {
		return (this->vkCode == other.vkCode
			 && this->scanCode == other.scanCode
			 && this->stroke == other.stroke);
	}
};

typedef std::span<KeyStroke> KeyStrokes;
