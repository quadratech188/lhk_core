#include <unordered_map>
#include <forward_list>

template <typename T> struct AttributeNode {
	std::unordered_map<int, AttributeNode<T>> nodes;
	std::forward_list<T> values;
};

template <typename T> class AttributeTree {
private:
	AttributeNode<T> root;

	void call(AttributeNode<T> node, int* attributes, int size, int currentIndex, void (*func)(T)) {
		if (node.nodes.empty()) {
			for (auto it: node.values) {
				func(it);
			}
			return;
		}

		call(node.nodes[attributes[currentIndex]], attributes, size, currentIndex + 1, func);
		call(node.nodes[0], attributes, size, currentIndex + 1, func);
	}

public:
	void insert(int* attributes, int size, T value) {
		auto current = root;
		for (int i = 0; i < size; i++) {
			current = current.nodes[i];
		}
		current.values.push_front(value);
	}

	void call(int* attributes, int size, void (*func)(T)) {
		call(root, attributes, size, 0,  func);
	}
};

