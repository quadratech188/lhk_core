#pragma once

#include <string>
#include <memory>

#include "AttributeTree.h"
#include "KeyboardSubHook.h"
#include <unordered_map>

namespace Layers {
	struct Layer {
		AttributeTree<KeyboardSubHook::SubHook> subHooks;
		bool activated;
	};

	extern std::unordered_map<std::string, std::shared_ptr<Layer>> layers;
	extern std::unordered_map<std::string, std::shared_ptr<Layer>> activatedLayers;

	bool exists(std::string name);
	bool activated(std::string name);
	void newLayer(std::string name);
	std::shared_ptr<Layer> get(std::string name);
	void activate(std::string name);
	void deactivate(std::string name);
}
