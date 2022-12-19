#include <iostream>
#include "Chat.h"
#include "ServiceFunc.h"

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


int Chat(Users& _users, Messages& _messages) {
	AtStart();

	bool doing = true;

	while (doing) {
		switch (get_command(GLOBAL_COMMANDS)) {	// получаем глобальную команду с консоли
			case 0:	// команда reg - зарегистрироваться
				(_users.NewUser()) ? (cout << "Вы успешно зарегистрированы!\n") : (cout << "Произошла ошибка регистрации.\n");	// создаём нового пользователя
				break;
			case 1:	// команда login - вход
				if (_users.Login()) {
					int unReadedMsgs = _messages.Find(_users.GetUserId());	// подсчёт числа непрочитанных сообщений
					if (unReadedMsgs > 0) {
						cout << "Есть непрочитанные сообщения (" << unReadedMsgs << "). ";
						if (QuestionYN("Показать?"))
							_messages.Read(_users.GetUserId(), true);	// вывод непрочитанных сообщений
					}
					// начало локального пространства команд
					while (_users.GetCurrentUser() != 0) {	// пока пользователь не вышел из чата
						switch (get_command(_users.GetUserLogin(), LOCAL_COMMANDS)) {	// получаем локальную команду с консоли
						case 0: {	// локальная команда send - отправить сообщение
								int receiverId = _users.ChooseUser();	// выбор получателя с возвратом его id
								if (receiverId != -1) {
									if (receiverId != _users.GetUserId()) {
										if (_messages.Add(_users.GetUserId(), _users.GetUserLogin(), receiverId, _users.GetUserLogin(receiverId)))
											cout << "Сообщение отправлено; id=" << _messages.GetLastMsgId() - 1 << '\n';
									}
									else
										cout << "Нельзя отправлять сообщения самому себе.\n";
								}
							}
							break;
						case 1:	// локальная команда read - прочитать сообщения
							_messages.Read(_users.GetUserId(), QuestionYN("Показать только непрочитанные (y) или все сообщения (n)?"));
							break;
						case 2:	// локальная команда info - вывести информацию о пользователе
							cout << "Информация о пользователе\n";
							_users.Show();
							break;
						case 3:	// локальная команда delete - удалить учётную запись пользователя
							if (QuestionYN("Информация о пользователе будет удалена. Вы уверены?"))
								_users.DeleteUser();
							break;
						case 4:	// локальная команда help - вывести справку по командам
							print_help(LOCAL_COMMANDS);
							break;
						case 5:	// локальная команда logout - выход
							_users.Logout();
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
				if (_users.GetIsChanged() && !_users.Save())	// сохраняем данные пользователей во внешний файл, если есть изменения
					return 1;
				if (_messages.GetIsChanged())	// сохраняем сообщения во внешний файл, если есть изменения
					_messages.Save();
				break;
			default:
				cout << "Команда не распознана, повторите ввод.\n";
		}
	}
	return 0;
}
