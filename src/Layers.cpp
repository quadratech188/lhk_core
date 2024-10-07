#include "Layers.h"

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <memory>

#include "LuaHeader.h"

namespace Layers {
	std::unordered_map<std::string, std::shared_ptr<Layer>> layers;
	std::unordered_map<std::string, std::shared_ptr<Layer>> activatedLayers;

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

		layers[name] = std::make_shared<Layer>();
	}

	std::shared_ptr<Layer> get(std::string name) {
		auto layer = layers.find(name);
		if (layer == layers.end()) {
			throw std::runtime_error("Key not found");
		}
				
		return layer->second;
	}

	void activate(std::string name) {
		std::shared_ptr<Layer> layer = get(name);

		layer->activated = true;

		activatedLayers[name] = layer;
	}

	void deactivate(std::string name) {
		auto layer = activatedLayers.find(name);

		if (layer == activatedLayers.end()) {
			throw std::runtime_error("Key not found");
		}

		layer->second->activated = false;

		activatedLayers.erase(layer);
	}
}
