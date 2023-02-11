#ifndef STACK_H
#define STACK_H

#include "DynamicArray.hpp"

template <typename T>
class Stack
{
public:
	Stack(std::initializer_list<T> list)
		: array_(list)
	{}

	void push(T element)
	{
		array_.append(std::move(element));
	}

	T pop()
	{
		const size_t last_index = array_.size() - 1;
		T element = std::move(array_[last_index]);

		array_.pop(last_index);

		return element;
	}

	bool is_empty() const
	{
		return array_.is_empty();
	}

	const T& last() const
	{
		return array_[array_.size() - 1];
	}
private:
	DynamicArray<T> array_;
};

#endif