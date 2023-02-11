#ifndef USER_H
#define USER_H



class User
{
public:
	User(const char* name, const char* email,
		const char* phoneNumber);

	User(
		const char* name, const char* email,
		const char* phoneNumber, const char* address
	);

	User(const User& user);

	User& operator=(const User & user) noexcept;

	User(User&& user) noexcept;

	User& operator=(User&& user) noexcept;

	~User();

	void swap(User& another) noexcept;

	void SetName(const char* name);

	[[nodiscard]] const char* Name() const noexcept;

	[[nodiscard]] const char* PhoneNumber() const noexcept;

	[[nodiscard]] const char* Address() const noexcept;
private:
	char* name_;
	char* email_;
	char* phoneNumber_;
	
	char* address_;
};

#endif