#include <iostream>
#include <string>
//#include <cstdlib>
#include <windows.h>
#include "Users.h"
#include "Messages.h"
#include "ServiceFunc.h"
#include "Constants.h"


using namespace std;


void print_help(const CommandSpace* _commandSpace) {	// печать справки по командам
	for (int i = 0; _commandSpace[i].command != ""; ++i)
		cout << "\t" << _commandSpace[i].command << "\t- " << _commandSpace[i].help << endl;
}


void AtStart() {	// начальные сообщения
	cout.clear();
	cout << "Здесь будет заголовок для чата!\n";
	cout << SEPARATOR;
	cout << "Выберите действие:\n";
	print_help(GLOBAL_COMMANDS);
	cout << SEPARATOR;
	cout << "Чат запущен " << GetTime() << endl;
	cout << SEPARATOR;
}


int _get_command(const CommandSpace* _commandSpace) {	// получение команды с консоли, выдача соотвествующего кода действия
	string command = get_value_from_console();
	lowercase(command);	//	преобразование текста команды в нижний регистр

	for (int i = 0; _commandSpace[i].command != ""; ++i)	// поиск кода команды
		if (command == _commandSpace[i].command)
			return i;

	return -1;
}


int get_command(const CommandSpace* _commandSpace) {	// получение команды с консоли, выдача соотвествующего кода действия
	cout << "Введите команду >> ";
	return _get_command(_commandSpace);
}


int get_command(const string& _str, const CommandSpace* _commandSpace) {	// получение команды с консоли, выдача соотвествующего кода действия
	cout << _str << ", введите команду >> ";
	return _get_command(_commandSpace);
}


int main() {
	system("chcp 1251");

	bool doing = true;
	bool logged = false;
	Users users;

	if (!users.Open()) {	// загружаем данные пользователей из внешнего файла
		cout << "Ошибка чтения файла данных!\n";	// ошибка будет при первом запуске чата, т.к. данные ещё не ни разу сохранялись
		if (QuestionYN("Завершить программу?"))
			return 1;	// аварийный выход по желанию пользователя
	}

	Messages messages;
	messages.Open();	// загружаем сообщения из внешнего файла

	AtStart();

	while (doing) {
		switch (get_command(GLOBAL_COMMANDS)) {	// получаем глобальную команду с консоли
			case 0:	// команда reg - зарегистрироваться
				(users.NewUser()) ? (cout << "Вы успешно зарегистрированы!\n") : (cout << "Произошла ошибка регистрации.\n");	// создаём нового пользователя
				break;
			case 1:	// команда login - вход
				if (users.Login()) {
					int unReadedMsgs = messages.Find(users.GetUserId());	// подсчёт числа непрочитанных сообщений
					if (unReadedMsgs > 0) {
						cout << "Есть непрочитанные сообщения (" << unReadedMsgs << "). ";
						if (QuestionYN("Показать?"))
							messages.Read(users.GetUserId(), true);	// вывод непрочитанных сообщений
					}
					logged = true;
					// начало локального пространства команд
					while (logged) {	// пока пользователь не вышел из чата
						switch (get_command(users.GetUserLogin(), LOCAL_COMMANDS)) {	// получаем локальную команду с консоли
						case 0: {	// локальная команда send - отправить сообщение
							int receiverId = users.ChooseUser();	// выбор получателя с возвратом его id
							if (receiverId != -1) {
								if (receiverId != users.GetUserId()) {
									if (messages.Add(users.GetUserId(), users.GetUserLogin(), receiverId, users.GetUserLogin(receiverId)))
										cout << "Сообщение отправлено; id=" << messages.GetLastMsgId() - 1 << '\n';
								}
								else
									cout << "Нельзя отправлять сообщения самому себе.\n";
							}
						}
							  break;
						case 1:	// локальная команда read - прочитать сообщения
							messages.Read(users.GetUserId(), QuestionYN("Показать только непрочитанные (y) или все сообщения (n)?"));
							break;
						case 2:	// локальная команда info - вывести информацию о пользователе
							cout << "Информация о пользователе\n";
							users.Show();
							break;
						case 3:	// локальная команда delete - удалить учётную запись пользователя
							if (QuestionYN("Информация о пользователе будет удалена. Вы уверены?")) {
								users.DeleteUser();
								logged = false;
							}
							break; 
						case 4:	// локальная команда help - вывести справку по командам
							print_help(LOCAL_COMMANDS);
							break;
						case 5:	// локальная команда logout - выход
							users.Logout();
							logged = false;
							break;
						default:
							cout << "Команда не распознана, повторите ввод.\n";
						}
					}// конец локального пространства команд
				}
				break;
			case 2:	// команда help - вывести справку по командам
				print_help(GLOBAL_COMMANDS);
				break;
			case 3:	// команда quit - закрыть чат
				doing = false;
				if (users.GetIsChanged() && !users.Save()) {	// сохраняем данные пользователей во внешний файл, если есть изменения
					cout << "Ошибка записи данных в файл!\n";
					return 1;
				}
				if (messages.GetIsChanged())	// сохраняем сообщения во внешний файл, если есть изменения
					messages.Save();
				break;
			default:
				cout << "Команда не распознана, повторите ввод.\n";
		}
	}
}