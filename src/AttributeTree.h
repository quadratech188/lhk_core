#pragma once

#include <unordered_map>
#include <forward_list>
#include <span>
#include <functional>

template <typename T> class AttributeTree {
private:
	
	template <typename K>
	struct AttributeNode {
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
		auto defaultIt = currentNode.nodes.find(0);
		if (defaultIt != currentNode.nodes.end()) {
			callIncludingDefault(indexArray, func, currentIndex + 1, defaultIt->second);
		}
	}
public:
	void callIncludingDefault(std::span<int> indexArray, std::function<void(T)> func) {
		callIncludingDefault(indexArray, func, 0, root);
	}

	std::forward_list<T>& query(std::span<int> indexArray) {
		AttributeNodeType* node = &root;
		for (const auto& it: indexArray) {
			node = &node->nodes[it];
		}
		return node->value;
	}
	void insert(std::span<int> indexArray, T data) {
		query(indexArray).push_front(data);
	}
};
