#pragma once
#include <string>
#include <vector>
#include "User.h"

class Users {
	private:
		std::vector<User> user;	// вектор с данными пользователей
		int usersCount = 0;	// количество пользователей
		int idsCount = 0; // количество использованных идентификаторов
		int currentUser = idsCount; // порядковый номер текущего пользователя (начинается с 1)
		bool isChanged = false;	// флаг наличия изменений в данных пользователей
		int FindLogin(const std::string& _login);	// проверка соответствия введённого login существующим; возврат порядкового номера в случае успеха
		void CheckArraySize();	// проверка наличия свободного места в векторе и его увеличение при необходимости
	public:
		Users();
		//~Users();
		bool NewUser();	// регистрация нового пользователя
		bool Login();	// вход пользователя в чат
		void Logout();	// выход пользователя из чата
		int ChooseUser();	// выбор получателя для отправки сообщения; возвращает id пользователя
		bool Open();	// чтение данных пользователей из внешнего файла
		bool Save();	// сохранение данных пользователей во внешний файл
		bool DeleteUser();	// удаление учётной записи пользователя
		void Show();	// отображение данных текущего пользователя
		void Show(const int _user_index);	// отображение данных указанного пользователя
		// getters
		int GetCurrentUser() const;	// порядковый номер текущего пользователя
		int GetUserId() const;	// id текущего пользователя
		int GetUserId(const int _user_index) const;	// id указанного пользователя
		std::string GetUserLogin() const;	// login текущего пользователя
		std::string GetUserLogin(const int _id) const;	// login указанного пользователя
		bool GetIsChanged() const;	// возврат флага наличия изменений в данных пользователей
};

