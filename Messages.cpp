#include <iostream>
#include <fstream>
#include <exception>
//#include <chrono>
#include <nlohmann/json.hpp>
#include <string>
#include "Messages.h"
#include "Message.h"
#include "ServiceFunc.h"
#include "Converter.h"
#include "Constants.h"


using json = nlohmann::json;
using namespace std;

//private:
void Messages::CheckArraySize() {	// проверка наличи€ свободного места в векторе и его увеличение при необходимости
	if (message.capacity() <= msgsCount)
		message.reserve(message.capacity() * 2);	//	при заполнении вектора каждый раз увеличиваем его Ємкость вдвое
}

//public:
Messages::Messages() {
	message.reserve(INITIAL_MSG_COUNT);
}


Messages::~Messages() {
}


bool Messages::Add(const int& _senderId, const std::string& _senderLogin, const int& _receiverId, const std::string& _receiverLogin) {	// добавление сообщени€
	CheckArraySize();

	cout << "¬ведите текст сообщени€: ";
	string text = get_string_from_console();

	if (!check_empty_name(text, "сообщение"))
		return false;

	message.emplace_back(msgsCount, _senderId, _senderLogin, _receiverId, _receiverLogin, GetTime(), text);	// вставка сообщени€ в конец вектора
	++msgsCount;
	isChanged = true;	// установка флага наличи€ изменений в массиве сообщений
	return true;
}


int Messages::Find(const int& _receiverId) const {	// подсчЄт непрочитанных сообщений
	int count = 0;
	for (int i = 0; i < msgsCount; i++)
		if ((message[i].receiverId == _receiverId) && (!message[i].wasReaded))
			count++;
	return count;
}


void Messages::Read(const int& _receiverId, const bool& _showUnReadedOnly) {	// вывод сообщений
	for (int i = 0; i < msgsCount; i++) {
		if ((message[i].receiverId == _receiverId) && (!_showUnReadedOnly || (!message[i].wasReaded))) {
			cout << "#" << message[i].id << " " << message[i].date_time << " от " << message[i].senderLogin << ": " << message[i].text << '\n';
			message[i].wasReaded = true;	// пометка прочитанным
			isChanged = true;	// установка флага наличи€ изменений в массиве сообщений
		}
	}
}


bool Messages::Open() {	// чтение сообщений из внешнего файла
	fstream msgs_data;
	msgs_data.open(MSG_DATA_FILE_NAME, ios::in);

	if (!msgs_data.is_open()) {
		cout << "Ќеизвестна€ ошибка!\n";
		return false;
	}

	bool result = false;
	json jsonObj;

	CheckArraySize();

	try {	// попытка создани€ json-объекта и чтени€ из него
		msgs_data >> jsonObj;

		for (int i = 0; i < jsonObj.size(); i++)
			message.emplace_back(
				jsonObj[i]["id"],
				jsonObj[i]["senderId"],
				utf8_to_cp1251(jsonObj[i]["senderLogin"]),	// перекодирование строк из UTF-8
				jsonObj[i]["receiverId"],
				utf8_to_cp1251(jsonObj[i]["receiverLogin"]),	// перекодирование строк из UTF-8
				utf8_to_cp1251(jsonObj[i]["date_time"]),	// перекодирование строк из UTF-8
				utf8_to_cp1251(jsonObj[i]["text"]),	// перекодирование строк из UTF-8
				jsonObj[i]["wasReaded"]);

		msgsCount = (int)jsonObj.size();
		result = true;
	}
	catch (exception& e) {
		cout << e.what() << endl;
		result = false;
	}
	msgs_data.close();
	return result;
}

bool Messages::Save() {	// сохранение сообщений во внешний файл
	fstream msgs_data;
	msgs_data.open(MSG_DATA_FILE_NAME, ios::out);

	if (!msgs_data.is_open()) {
		cout << "Ќеизвестна€ ошибка!\n";
		return false;
	}

	bool result = false;
	json jsonObj;

	try {	// попытка создани€ json-объекта и записи в него
		for (int i = 0; i < msgsCount; i++) {
			jsonObj[i]["id"] = message[i].id;
			jsonObj[i]["senderId"] = message[i].senderId;
			jsonObj[i]["senderLogin"] = cp1251_to_utf8(message[i].senderLogin);	// перекодирование строк в UTF-8
			jsonObj[i]["receiverId"] = message[i].receiverId;
			jsonObj[i]["receiverLogin"] = cp1251_to_utf8(message[i].receiverLogin);	// перекодирование строк в UTF-8
			jsonObj[i]["date_time"] = cp1251_to_utf8(message[i].date_time);	// перекодирование строк в UTF-8
			jsonObj[i]["text"] = cp1251_to_utf8(message[i].text);	// перекодирование строк в UTF-8
			jsonObj[i]["wasReaded"] = message[i].wasReaded;
		}
		msgs_data << setw(4) << jsonObj;
		result = true;
	}
	catch (exception& e) {
		cout << e.what() << endl;
		result = false;
	}
	msgs_data.close();
	return result;
}


int Messages::GetLastMsgId() const {	// количество сообщений
	return msgsCount;
}


bool Messages::GetIsChanged() const {	// возврат флага наличи€ изменений в сообщени€х
	return isChanged;
}