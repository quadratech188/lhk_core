#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "AttributeTree.h"
#include "KeyboardSubHook.h"

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
