#include <cstring>
#include <algorithm>

#include "User.hpp"

User::User(const char* name, const char* email,
	const char* phoneNumber) :
	address_{ new char[1] {""} }
{
	const size_t nameSize = strlen(name) + 1;
	name_ = new char[nameSize];
	strcpy_s(name_, nameSize, name);

	const size_t emailSize = strlen(email) + 1;
	email_ = new char[emailSize];
	strcpy_s(email_, emailSize, email);

	const size_t phoneNumberSize = strlen(phoneNumber) + 1;
	phoneNumber_ = new char[phoneNumberSize];
	strcpy_s(phoneNumber_, phoneNumberSize, phoneNumber);
}

User::User(
	const char* name, const char* email,
	const char* phoneNumber, const char* address
) : User(name, email, phoneNumber)
{
	delete[] address_;
	const size_t addressSize = strlen(address) + 1;
	address_ = new char[addressSize];
	strcpy_s(address_, addressSize, address);
}

User::User(const User& user) :
	User(user.name_, user.email_,
		user.phoneNumber_, user.address_)
{}

User& User::operator=(const User & user) noexcept
{
	User user_copy(user);

	this->swap(user_copy);
	
	return *this;
}

User::User(User&& user) noexcept
	: name_(user.name_),
	email_(user.email_),
	phoneNumber_(user.phoneNumber_),
	address_(user.address_)
{
	user.name_ = nullptr;
	user.email_ = nullptr;
	user.phoneNumber_ = nullptr;
	user.address_ = nullptr;
}

User& User::operator=(User&& user) noexcept
{
	if (this == &user)
		return *this;

	delete[] name_;
	delete[] email_;
	delete[] phoneNumber_;
	delete[] address_;

	name_ = user.name_;
	email_ = user.email_;
	phoneNumber_ = user.phoneNumber_;
	address_ = user.address_;

	user.name_ = nullptr;
	user.email_ = nullptr;
	user.phoneNumber_ = nullptr;
	user.address_ = nullptr;

	return *this;
}

User::~User()
{
	delete[] name_;
	delete[] email_;
	delete[] phoneNumber_;
	delete[] address_;
}

void User::swap(User& another) noexcept
{
	using std::swap;

	swap(another.name_, name_);
	swap(another.email_, email_);
	swap(another.phoneNumber_, phoneNumber_);
	swap(another.address_, address_);
}

void User::SetName(const char* name)
{
	const size_t newSize = strlen(name) + 1;

	name_ = new char[newSize];

	strcpy_s(name_, newSize, name);
}

[[nodiscard]] const char* User::Name() const noexcept
{
	return name_;
}

[[nodiscard]] const char* User::PhoneNumber() const noexcept
{
	return phoneNumber_;
}

[[nodiscard]] const char* User::Address() const noexcept
{
	return address_;
}