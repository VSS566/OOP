#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <optional>

template <typename T>
class Array
{
public:
	Array(std::initializer_list<T> list)
		: size_(list.size()),
		pointer_(new T[size_]{})
	{
		size_t i = 0;
		for (const T& element : list)
		{
			if (i >= size_)
				break;
			pointer_[i] = element;
			i++;
		}
	}

	Array(const T array[],
		const size_t new_size,
		const size_t argument_size)
		: size_(new_size), pointer_(new T[new_size]{})
	{
		const size_t min_size = std::min(
			argument_size,
			new_size
		);
		for (size_t i = 0; i < min_size; i++) {
			pointer_[i] = array[i];
		}
	}

	Array(const Array& another)
		: Array(another.pointer_, another.size())
	{}

	Array(const Array& another, size_t new_size)
		: Array(another.pointer_, new_size, another.size())
	{}

	Array& operator=(const Array& another)
	{
		if (&another == this)
			return *this;
		
		Array copy(another);
		std::swap(size_, copy.size_);
		std::swap(pointer_, copy.pointer_);

		return *this;
	}

	Array(Array&& another) noexcept
		: size_(std::exchange(another.size_, 0ull)),
		pointer_(std::exchange(another.pointer_, nullptr))
	{}

	Array& operator=(Array&& another) noexcept
	{
		if (&another == this)
			return *this;

		delete[] pointer_;
		
		size_ = std::exchange(another.size_, 0ull);
		pointer_ = std::exchange(another.pointer_, nullptr);

		return *this;
	}

	~Array()
	{
		delete[] pointer_;
	}

	T& operator[](size_t index)
	{
		if (index >= size_)
			throw std::out_of_range("Index is out of range");
		return pointer_[index];
	}

	const T& operator[](size_t index) const
	{
		if (index >= size_)
			throw std::out_of_range("Index is out of range");
		return pointer_[index];
	}

	// getter / accessor
	const size_t& size() const
	{
		return size_;
	}

	template <class U>
	friend std::ostream& operator<<(
		std::ostream& out, 
		const Array<U>& array);
private:
	size_t size_;
	T* pointer_;

	Array(const T array[],
		const size_t size)
		: size_(size), pointer_(new T[size])
	{
		for (size_t i = 0; i < size; i++)
			pointer_[i] = array[i];
	}
};

template <typename T>
std::ostream& operator<<(
	std::ostream& out, 
	const Array<T>& array)
{
	out << '[';
	if (array.size_ > 0)
	{
		for (size_t i = 0; i < array.size_-1; i++)
		out << array.pointer_[i] << ", ";
		out << array.pointer_[array.size_-1];
	}
	out << "]\n";

	return out;
}



#endif