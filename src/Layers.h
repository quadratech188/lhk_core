#pragma once

#include <string>
#include <unordered_map>

#include "AttributeTree.h"
#include "KeyboardSubHook.h"

namespace Layers {
	struct Layer {
		AttributeTree<KeyboardSubHook::SubHook> subHooks;
		bool activated;
	};

	extern std::unordered_map<std::string, Layer> layers;
	typedef decltype(layers)::iterator LayerIt;
	extern std::unordered_map<std::string, LayerIt> activatedLayers;

	bool exists(std::string name);
	bool activated(std::string name);
	void newLayer(std::string name);
	LayerIt get(std::string name);
	void activate(std::string name);
	void deactivate(std::string name);
}
