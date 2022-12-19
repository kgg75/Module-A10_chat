#include <iostream>
#include "Chat.h"
#include "ServiceFunc.h"

using namespace std;


void print_help(const CommandSpace* _commandSpace) {	// ������ ������� �� ��������
	for (int i = 0; _commandSpace[i].command != ""; ++i)
		cout << "\t" << _commandSpace[i].command << "\t- " << _commandSpace[i].help << endl;
}


void AtStart() {	// ��������� ���������
	cout.clear();
	cout << "����� ����� ��������� ��� ����!\n";
	cout << SEPARATOR;
	cout << "�������� ��������:\n";
	print_help(GLOBAL_COMMANDS);
	cout << SEPARATOR;
	cout << "��� ������� " << GetTime() << endl;
	cout << SEPARATOR;
}


int _get_command(const CommandSpace* _commandSpace) {	// ��������� ������� � �������, ������ ��������������� ���� ��������
	string command = get_value_from_console();
	lowercase(command);	//	�������������� ������ ������� � ������ �������

	for (int i = 0; _commandSpace[i].command != ""; ++i)	// ����� ���� �������
		if (command == _commandSpace[i].command)
			return i;

	return -1;
}


int get_command(const CommandSpace* _commandSpace) {	// ��������� ������� � �������, ������ ��������������� ���� ��������
	cout << "������� ������� >> ";
	return _get_command(_commandSpace);
}


int get_command(const string& _str, const CommandSpace* _commandSpace) {	// ��������� ������� � �������, ������ ��������������� ���� ��������
	cout << _str << ", ������� ������� >> ";
	return _get_command(_commandSpace);
}


int Chat(Users& _users, Messages& _messages) {
	AtStart();

	bool doing = true;

	while (doing) {
		switch (get_command(GLOBAL_COMMANDS)) {	// �������� ���������� ������� � �������
			case 0:	// ������� reg - ������������������
				(_users.NewUser()) ? (cout << "�� ������� ����������������!\n") : (cout << "��������� ������ �����������.\n");	// ������ ������ ������������
				break;
			case 1:	// ������� login - ����
				if (_users.Login()) {
					int unReadedMsgs = _messages.Find(_users.GetUserId());	// ������� ����� ������������� ���������
					if (unReadedMsgs > 0) {
						cout << "���� ������������� ��������� (" << unReadedMsgs << "). ";
						if (QuestionYN("��������?"))
							_messages.Read(_users.GetUserId(), true);	// ����� ������������� ���������
					}
					// ������ ���������� ������������ ������
					while (_users.GetCurrentUser() != 0) {	// ���� ������������ �� ����� �� ����
						switch (get_command(_users.GetUserLogin(), LOCAL_COMMANDS)) {	// �������� ��������� ������� � �������
						case 0: {	// ��������� ������� send - ��������� ���������
								int receiverId = _users.ChooseUser();	// ����� ���������� � ��������� ��� id
								if (receiverId != -1) {
									if (receiverId != _users.GetUserId()) {
										if (_messages.Add(_users.GetUserId(), _users.GetUserLogin(), receiverId, _users.GetUserLogin(receiverId)))
											cout << "��������� ����������; id=" << _messages.GetLastMsgId() - 1 << '\n';
									}
									else
										cout << "������ ���������� ��������� ������ ����.\n";
								}
							}
							break;
						case 1:	// ��������� ������� read - ��������� ���������
							_messages.Read(_users.GetUserId(), QuestionYN("�������� ������ ������������� (y) ��� ��� ��������� (n)?"));
							break;
						case 2:	// ��������� ������� info - ������� ���������� � ������������
							cout << "���������� � ������������\n";
							_users.Show();
							break;
						case 3:	// ��������� ������� delete - ������� ������� ������ ������������
							if (QuestionYN("���������� � ������������ ����� �������. �� �������?"))
								_users.DeleteUser();
							break;
						case 4:	// ��������� ������� help - ������� ������� �� ��������
							print_help(LOCAL_COMMANDS);
							break;
						case 5:	// ��������� ������� logout - �����
							_users.Logout();
							break;
						default:
							cout << "������� �� ����������, ��������� ����.\n";
						}
					}// ����� ���������� ������������ ������
				}
				break;
			case 2:	// ������� help - ������� ������� �� ��������
				print_help(GLOBAL_COMMANDS);
				break;
			case 3:	// ������� quit - ������� ���
				doing = false;
				if (_users.GetIsChanged() && !_users.Save())	// ��������� ������ ������������� �� ������� ����, ���� ���� ���������
					return 1;
				if (_messages.GetIsChanged())	// ��������� ��������� �� ������� ����, ���� ���� ���������
					_messages.Save();
				break;
			default:
				cout << "������� �� ����������, ��������� ����.\n";
		}
	}
	return 0;
}
