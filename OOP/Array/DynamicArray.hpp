#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.hpp"

template <typename T>
class DynamicArray 
{
public:
	DynamicArray(Array<T> array)
		: size_(array.size()), array_(std::move(array))
	{
		if (capacity() == 0)
			reallocate(Array{ 0 });
	}

	DynamicArray(std::initializer_list<T> list)
		: size_(list.size()), array_(list)
	{
		if (capacity() == 0)
			reallocate(Array{ 0 });
	}

	void reallocate(size_t new_size)
	{
		array_ = std::move(Array<T>(array_, new_size));
	}

	void free_extra_memory()
	{
		if (size_ == capacity())
			return;
		reallocate(size_);
	}

	void append(T element)
	{
		if (size_ >= capacity()) {
			reallocate(capacity()*2);
		}

		array_[size_] = std::move(element);
		size_++;
	}

	void pop(const size_t index)
	{
		for (size_t i = index+1; i < size_; i++)
		{
			array_[i - 1] = array_[i];
		}
		size_--;
	}

	void clear()
	{
		size_ = 0;
	}

	T& operator[](size_t index)
	{
		if (index >= size_)
			throw std::out_of_range("index is out of range");
		return array_[index];
	}

	const T& operator[](size_t index) const
	{
		return array_[index];
	}

	const size_t& capacity() const
	{
		return array_.size();
	}

	const size_t& size() const
	{
		return size_;
	}

	const bool is_empty() const
	{
		return size_ == 0;
	}

	template <class U>
	friend std::ostream& operator<<(
		std::ostream& out,
		const DynamicArray<U>& array);
private:
	size_t size_;
	Array<T> array_;

	void reallocate(Array<T> new_array)
	{
		array_ = std::move(new_array);
	}
};

template <typename T>
std::ostream& operator<<(
	std::ostream& out,
	const DynamicArray<T>& array)
{
	out << '[';
	if (array.size_ > 0)
	{
		for (size_t i = 0; i < array.size_ - 1; i++)
			out << array.array_[i] << ", ";
		out << array.array_[array.size_ - 1];
	}
	out << "]\n";

	return out;
}

#endif