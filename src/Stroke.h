#pragma once

#include <string>

#include "LuaHeader.h"

struct Stroke {
	enum Value {
		PRESS,
		RELEASE,
		MIRROR
	};
	Stroke(Value value): value(value) {};
	Stroke(lua_State* L, int index);
	Stroke(): value(PRESS) {};

	bool operator==(const Stroke& other) const {
		return value == other.value;
	}
	bool operator==(const Value& other) const {
		return value == other;
	}

	operator std::string() const;
	operator int() const;

	bool isRelease() const;
private:
	Value value;
};
