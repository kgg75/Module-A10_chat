#include <iostream>
#include <fstream>
#include <exception>
#include <nlohmann/json.hpp>
#include "Users.h"
#include "ServiceFunc.h"
#include "Converter.h"
#include "Constants.h"


using json = nlohmann::json;
using namespace std;

//private:
int Users::FindLogin(const string& _login) {	// проверка соответствия введённого login существующим; возврат порядкового номера в случае успеха
	for (int i = 1; i <= usersCount; i++)
		if (_login == user[i].login) return i;
	cout << "Пользователь с таким именем не существует!\n";
	return 0;
}


void Users::CheckArraySize() {	// проверка наличия свободного места в векторе и его увеличение при необходимости
	if (user.capacity() <= usersCount)
		user.reserve(user.capacity() * 2);	//	при заполнении вектора каждый раз увеличиваем его ёмкость вдвое
}


//public:
Users::Users() {
	user.reserve(INITIAL_COUNT);
	user.emplace_back(0, SERVICE_NAME, SERVICE_LOGIN, "");
}


//Users::~Users() {}


bool Users::NewUser() {	// регистрация нового пользователя
	CheckArraySize();

	string name, login, password, password2;

	cout << "Для регистрации введите следующие данные пользователя:\n";
	cout << "Фамилия, имя (длина " << MIN_NAME_LENGTH << "-" << MAX_NAME_LENGTH << " символов, пробелы разрешены): "; //cin >> _name;
	name = get_string_from_console();

	if (!check_name(name, "имя", MIN_NAME_LENGTH, MAX_NAME_LENGTH))
		return false;

	cout << "Учётное имя (login) (длина " << MIN_LOGIN_LENGTH << "-" << MAX_LOGIN_LENGTH << " символов, пробелы не допускаются): ";
	login = get_string_from_console();
	if (!check_name(login, "login", MIN_LOGIN_LENGTH, MAX_LOGIN_LENGTH) || !check_spaces(login,"login"))
		return false;

	if (lowercase_s(login) == SERVICE_LOGIN) {
		cout << "Регистрироваться под таким именем нельзя!" << endl;
		return false;
	}

	cout << "Пароль: ";
	password = get_value_from_console();
	if (!check_name(password, "пароль", MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH) || !check_spaces(password, "пароль"))
		return false;

	cout << "Повторите пароль: ";
	password2 = get_value_from_console();
	if (password != password2) {
		cout << "Пароли не совпадают!" << endl;
		return false;
	}

	idsCount++;
	usersCount++;
	currentUser = usersCount;

	user.emplace_back(idsCount, name, login, password, false, true);

	isChanged = true;
	return true;
}


bool Users::Login() {	// вход пользователя в чат
	string login;
	cout << "Укажите условное имя (login): "; cin >> login;

	if (!check_empty_name(login, "имя"))
		return false;

	int findedUser = FindLogin(login);
	if (findedUser == 0)
		return false;

	string password;
	cout << "Укажите пароль: "; cin >> password;

	if (password != user[findedUser].password) {
		cout << "Неверный пароль!" << endl;
		return false;
	}

	currentUser = findedUser;
	user[currentUser].logged = true;
	cout << "Пользователь " << user[currentUser].login << " вошёл в чат." << endl;

	return true;
}


void Users::Logout() {	// выход пользователя из чата
	user[currentUser].logged = false;
	cout << "Пользователь " << user[currentUser].login << " вышел из чата." << endl;
	currentUser = 0;	// текущий служебный пользователь 'all'
}


int Users::ChooseUser() {	// выбор получателя для отправки сообщения; возвращает id пользователя
	string login;
	cout << "Укажите условное имя (login) получателя: "; cin >> login;

	if (!check_empty_name(login, "имя"))
		return -1;

	int findedUser = FindLogin(login);
	if (findedUser == 0)	// введённый login не найден
		return -1;

	return user[findedUser].id;
}


bool Users::DeleteUser() {	// удаление учётной записи пользователя
	user.erase(user.begin() + currentUser);
	usersCount--;
	currentUser = 0;
	isChanged = true;
	return true;
}


bool Users::Open() {	// чтение данных пользователей из внешнего файла
	fstream users_data;
	users_data.open(USER_DATA_FILE_NAME, ios::in);

	if (!users_data.is_open()) {
		cout << "Неизвестная ошибка!\n";
		return false;
	}

	bool result = false;
	json jsonObj;

	CheckArraySize();

	try {	// попытка создания json-объекта и чтения из него
		users_data >> jsonObj;

		for (int i = 0; i < jsonObj.size(); i++)
			user.emplace_back(
				jsonObj[i]["id"],
				utf8_to_cp1251(jsonObj[i]["name"]),	// перекодирование строк из UTF-8
				utf8_to_cp1251(jsonObj[i]["login"]),	// перекодирование строк из UTF-8
				utf8_to_cp1251(jsonObj[i]["password"]),	// перекодирование строк из UTF-8
				jsonObj[i]["locked"],
				false);

		usersCount = (int)jsonObj.size();
		idsCount = user[usersCount].id;
		result = true;
	}
	catch (exception& e) {
		cout << e.what() << endl;
		cout << "Ошибка чтения файла данных!\n";	// ошибка будет при первом запуске чата, т.к. данные ещё не ни разу сохранялись
		result = false;
	}
	users_data.close();
	return result;
}

bool Users::Save() {	// сохранение данные пользователей во внешний файл
	fstream users_data;
	users_data.open(USER_DATA_FILE_NAME, ios::out);

	if (!users_data.is_open()) {
		cout << "Неизвестная ошибка!\n";
		return false;
	}

	bool result = false;
	json jsonObj;

	try {	// попытка создания json-объекта и записи в него
		for (int i = 0; i < usersCount; i++) {
			jsonObj[i]["id"] = user[i + 1].id;
			jsonObj[i]["name"] = cp1251_to_utf8(user[i + 1].name);	// перекодирование строк в UTF-8
			jsonObj[i]["login"] = cp1251_to_utf8(user[i + 1].login);	// перекодирование строк в UTF-8
			jsonObj[i]["password"] = cp1251_to_utf8(user[i + 1].password);	// перекодирование строк в UTF-8
			jsonObj[i]["locked"] = user[i + 1].locked;
		}
		users_data << setw(4) << jsonObj;
		result = true;
	}
	catch (exception& e) {
		cout << e.what() << endl;
		cout << "Ошибка записи данных в файл!\n";
		result = false;
	}
	users_data.close();
	return result;
}


void Users::Show() {	// отображение данных текущего пользователя
	Show(currentUser);
}


void Users::Show(const int _user_index) {	// отображение данных указанного пользователя
	cout << "\tid \t= " << user[_user_index].id << endl;
	cout << "\tname\t= " << user[_user_index].name << endl;
	cout << "\tlogin\t= " << user[_user_index].login << endl;
	cout << "\tpassword\t= " << user[_user_index].password << endl;
	cout << "\tlocked\t= " << user[_user_index].locked << endl;
	cout << "\tlogged\t= " << user[_user_index].logged << endl;
}


int Users::GetCurrentUser() const {	// порядковый номер текущего пользователя
	return currentUser;
}


int Users::GetUserId() const {	// id текущего пользователя
	return user[currentUser].id;
}

int Users::GetUserId(const int _user_index) const {	// id указанного пользователя
	return user[_user_index].id;
}


std::string Users::GetUserLogin() const {	// login текущего пользователя
	return user[currentUser].login;
}


std::string Users::GetUserLogin(const int _id) const {	// login указанного пользователя
	for (int i=0; i < usersCount; i++)
		if (user[i].id == _id)
			return user[i].login;
	return "";
}


bool Users::GetIsChanged() const {
	return isChanged;
}