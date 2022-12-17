#pragma once
//#include <string>

struct CommandSpace {	// структура описывает связку команда-подсказка
	const char* command;
	const char* help;
};

const CommandSpace GLOBAL_COMMANDS[] = {	// пространство глобальных команд с подсказками
	{"reg", "зарегистрироваться"},
	{"login", "войти в чат"},
	{"help", "вывести справку по командам"},
	{"quit", "закрыть чат"},
	{"", ""}
};

const CommandSpace LOCAL_COMMANDS[] = {		// пространство локальных команд с подсказками
	{"send", "отправить сообщение"},
	{"read", "прочитать сообщения"},
	{"info", "вывести информацию о пользователе"},
	{"delete", "удалить учётную запись пользователя"},
	{"help", "вывести справку по командам"},
	{"logout", "выйти из чата"},
	{"", ""}
};

const int MIN_NAME_LENGTH = 2;	// минимальная длина имени пользователя
const int MAX_NAME_LENGTH = 32;	// максимальная длина имени пользователя
const int MIN_LOGIN_LENGTH = 2;	// минимальная длина login
const int MAX_LOGIN_LENGTH = 16;	// максимальная длина login
const int MIN_PASSWORD_LENGTH = 3;	// минимальная длина пароля
const int MAX_PASSWORD_LENGTH = 8;	// максимальная длина пароля
const int INITIAL_COUNT = 2;	// начальная длина массива с данными пользователей; минимальное значение=2 задано только для тестирования!!
const int INITIAL_MSG_COUNT = 2;	// начальная длина массива с сообщениями; минимальное значение=2 задано только для тестирования!!
const char SERVICE_NAME[] = {"все пользователи" };	// имя служебного пользователя с индексом 0
const char SERVICE_LOGIN[] = {"all"};	// login служебного пользователя с индексом 0
const char USER_DATA_FILE_NAME[] = {"users.json"};	// имя файла для хранения данных пользователей
const char MSG_DATA_FILE_NAME[] = {"msgs.json"};	// имя файла для хранения сообщений
const char SEPARATOR[] = {"-------------------------------------------------------------------------\n"};
const char DATE_TIME_FORMAT[] = {"[%Y-%m-%d %H:%M:%S]"};