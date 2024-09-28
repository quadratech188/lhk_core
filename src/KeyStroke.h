#pragma once

#include <windows.h>
#include <span>

#include "LuaHeader.h"

typedef bool STROKE;
#define STROKEDOWN false
#define STROKEUP true

struct KeyStroke {
	DWORD vkCode;
	DWORD scanCode;
	STROKE stroke;
	KeyStroke(WPARAM, LPARAM);
	KeyStroke();
	bool operator==(const KeyStroke& other) const {
		return (this->vkCode == other.vkCode
			 && this->scanCode == other.scanCode
			 && this->stroke == other.stroke);
	}
};

typedef std::span<KeyStroke> KeyStrokes;
