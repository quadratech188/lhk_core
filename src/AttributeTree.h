#pragma once

#include <iostream>
#include <memory>
#include <optional>
#include <unordered_map>
#include <forward_list>
#include <span>
#include <functional>

template <typename T> class AttributeTree {
private:
	
	template <typename K>
	struct AttributeNode {
		std::unique_ptr<AttributeNode<K>> defaultNode;
		std::unordered_map<int, AttributeNode<K>> nodes;
		K value;
	};

	typedef AttributeNode<std::forward_list<T>> AttributeNodeType;

	AttributeNodeType root;

	void callIncludingDefault(std::span<int> indexArray, std::function<void(T)> func, int currentIndex, AttributeNodeType& currentNode) {
		if (indexArray.size() == currentIndex) {
			for (auto& it: currentNode.value) {
				func(it);
			}
			return;
		}

		auto it = currentNode.nodes.find(indexArray[currentIndex]);
		if (it != currentNode.nodes.end()) {
			callIncludingDefault(indexArray, func, currentIndex + 1, it->second);
		}
		if (currentNode.defaultNode != nullptr) {
			callIncludingDefault(indexArray, func, currentIndex + 1, *currentNode.defaultNode);
		}
	}
public:
	void callIncludingDefault(std::span<int> indexArray, std::function<void(T)> func) {
		callIncludingDefault(indexArray, func, 0, root);
	}

	std::forward_list<T>& query(std::span<std::optional<int>> indexArray) {
		AttributeNodeType* node = &root;
		for (const auto& it: indexArray) {
			if (it.has_value()) {
				node = &node->nodes[it.value()];
			}
			else {
				if (node->defaultNode == nullptr) {
					node->defaultNode = std::make_unique<AttributeNodeType>();
				}
				// Workaround
				node = node->defaultNode.get();
			}
		}
		return node->value;
	}
	void insert(std::span<std::optional<int>> indexArray, T data) {
		query(indexArray).push_front(data);
	}
};
