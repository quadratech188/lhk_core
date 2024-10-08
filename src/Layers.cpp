#include "Layers.h"

#include <stdexcept>
#include <string>
#include <unordered_map>

#include "LuaHeader.h"

namespace Layers {
	std::unordered_map<std::string, Layer> layers;
	std::unordered_map<std::string, LayerIt> activatedLayers;

	bool exists(std::string name) {
		auto layer = layers.find(name);

		return layer != layers.end();
	}

	bool activated(std::string name) {
		auto layer = activatedLayers.find(name);

		return layer != activatedLayers.end();
	}

	void newLayer(std::string name) {
		if (exists(name)) {
			throw std::runtime_error("Key already exists");
		}

		layers[name] = Layer();
	}

	LayerIt get(std::string name) {
		auto layer = layers.find(name);
		if (layer == layers.end()) {
			throw std::runtime_error("Key not found");
		}
				
		return layer;
	}

	void activate(std::string name) {
		auto layer = get(name);

		layer->second.activated = true;

		activatedLayers[name] = layer;
	}

	void deactivate(std::string name) {
		auto layer = activatedLayers.find(name);

		if (layer == activatedLayers.end()) {
			throw std::runtime_error("Key not found");
		}

		layer->second->second.activated = false;

		activatedLayers.erase(layer);
	}
}
