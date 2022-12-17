#pragma once
#include <string>


struct User {
	int id;	// уникальный идентификатор
	std::string name;	// полное имя
	std::string login;	// учётное имя (login)
	std::string password;	// пароль
	bool locked = false;	// флаг блокировки пользователя (зарезервирован)
	bool logged = false;	// флаг, указывающий на вход пользователя

	User(const int id,
		const std::string name,
		const std::string login,
		const std::string password,
		const bool locked = false,
		const bool logged = false);
};

