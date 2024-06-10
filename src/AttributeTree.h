#pragma once

template <typename T> class AttributeTree {
public:
	void insert(int* attributes, int size, T value);
	void call(int* attributes, int size);
};
