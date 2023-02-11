#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <memory>

template <typename T>
class LinkedList
{
public:
	struct Node;
	using NodePtr = std::unique_ptr<Node>;

	struct Node
	{
		T value;
		NodePtr next = nullptr;
	};

	

	T& operator[](size_t index) {
		NodePtr selected {first_node_};

		for (size_t i = 0; i < index; i++)
		{
			if (selected == nullptr)
				throw std::out_of_range(
					"index is out of boundaries"
				);
			selected = selected->next;
		}

		return first_node_.value;
	}

	const T& operator[](size_t index) const {
		NodePtr selected{ first_node_ };

		for (size_t i = 0; i < index; i++)
		{
			if (selected == nullptr)
				throw std::out_of_range(
					"index is out of boundaries"
				);
			selected = selected->next;
		}

		return first_node_.value;
	}

	[[nodiscard]] const size_t& size() const
	{
		return size_;
	}
private:
	Node first_node_;
	size_t size_;
};

template <typename T>
struct Node
{
	T value;

	Node* next = nullptr;
};

template <typename T>
void print_list(const Node<T>& list)
{
	Node<T> const* current = &list;

	while (current != nullptr)
	{
		std::cout << current->value;
		current = current->next;
	}
}

template <typename T>
bool is_looped_list(const Node<T>& list)
{
	Node<T> const* faster = &list;
	Node<T> const* slower = &list;
	do {
		if (faster->next == nullptr
			|| faster->next->next == nullptr)
			return false;
		faster = faster->next->next;
		slower = slower->next;
	} while (faster != slower);

	return true;
}

#endif