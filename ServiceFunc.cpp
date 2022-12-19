#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "ServiceFunc.h"
#include "Constants.h"


using namespace std;


void lowercase(string& _str) {	// преобразование строки в нижний регистр
	for (int i = 0; _str[i] != 0; ++i)
		if (_str[i] >= 'A' && _str[i] <= 'Z')
			_str[i] += 'a' - 'A';
}

string lowercase_s(const string& _str) {	// преобразование строки в нижний регистр
	string __str = _str;
	for (int i = 0; __str[i] != 0; ++i)
		if (__str[i] >= 'A' && __str[i] <= 'Z')
			__str[i] += 'a' - 'A';
	return __str;
}


bool check_empty_name(const string& _str, const string& _subject) {	// проверки строки на пустоту
	if (_str.empty()) {
		cout << "Ошибка - " << _subject << " не может быть пустым.\n";
		return false;
	}
	return true;
}


bool check_spaces(const string& _str, const string& _subject) {	// проверки строки на пробелы
	if (_str.find_first_of(' ') != string::npos) {	// найдены пробелы
		cout << "Ошибка - " << _subject << " не может содержать пробелы.\n";
		return false;
	}
	return true;
}


bool check_name(const string& _str, const string& _subject, const int& _minLength, const int& _maxLength) {	// проверки строки на пустоту, минимальную/максимальную длину
	if (!check_empty_name(_str, _subject))
		return false;
	if ((_str.size() < _minLength) || (_str.size() > _maxLength)) {
		cout << "Ошибка - длина значения вне допустимого диапазона [" << _minLength << "-" <<_maxLength << "].\n";
		return false;
	}
	return true;
}


std::string get_value_from_console() {	// получение значения с консоли
	std::string value;
	while (!(cin >> value));	// noskipws?
	std::cin.clear(),
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// очистка буфера консоли
	return value;
}


std::string get_string_from_console() {	// получение строки с консоли и её очистка от начальных и конечных пробелов
	std::string str;
	while (str.empty())
		std::getline(cin, str);
	str.erase(0, str.find_first_not_of(' '));
	str.erase(str.find_last_not_of(' ') + 1, str.length());
	return str;
}


std::string GetTime() {	// получение текущего времени
	const time_t t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::stringstream ss;
	ss << std::put_time(std::localtime(&t_c), DATE_TIME_FORMAT);	// "[%Y-%m-%d %H:%M:%S].\n";
	return ss.str();
}


bool QuestionYN(const string& _str) {	// вопрос с двумя вариантами ответа y/n
	cout << _str << " (y/n): ";
	string command = "";
	while ((command != "y") && (command != "n"))
		command = get_value_from_console();
	return (command == "y") ? true : false;
}

