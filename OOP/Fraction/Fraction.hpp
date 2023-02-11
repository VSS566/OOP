#ifndef FRACTION_H
#define FRACTION_H

#include <numeric>

template <typename T>
class Fraction
{
public:
	Fraction(T numerator, T denominator)
		: numerator_(numerator), denominator_(denominator)
	{}
	
	Fraction& reduce()
	{
		T gcd = std::gcd(numerator_, denominator_);

		numerator_ /= gcd;
		denominator_ /= gcd;

		return *this;
	}
	
	[[nodiscard]] Fraction operator+(
		const Fraction& another
		) const noexcept
	{
		return std::move(Fraction(
			numerator_ * another.denominator_
			+ another.numerator_ * denominator_,
			denominator_ * another.denominator_
		).reduce());
	}

	Fraction& operator+=(const Fraction& another)
	{
		*this = *this + another;
		return *this;
	}

	std::strong_ordering operator<=>(const Fraction& another) const
	{
		T numerator, another_numerator;

		if (denominator_ != another.denominator_) {
			numerator = numerator_ * another.denominator_;
			another_numerator = another.numerator_ + denominator_;
		} else
		{
			numerator = numerator_;
			another_numerator = another.numerator_;
		}

		if (numerator < another_numerator)
			return std::strong_ordering::less;
		if (numerator > another_numerator)
			return std::strong_ordering::greater;
		return std::strong_ordering::equal;
	}

	bool operator==(const Fraction& another) const
	{
		return (*this <=> another) == std::strong_ordering::equal;
	}

	[[nodiscard]] const T& numerator() const noexcept
	{
		return numerator_;
	}

	[[nodiscard]] const T& denominator() const noexcept
	{
		return denominator_;
	}
private:
	T numerator_, denominator_;
};

#endif