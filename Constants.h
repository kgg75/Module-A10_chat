#pragma once
//#include <string>

struct CommandSpace {	// ��������� ��������� ������ �������-���������
	const char* command;
	const char* help;
};

const CommandSpace GLOBAL_COMMANDS[] = {	// ������������ ���������� ������ � �����������
	{"reg", "������������������"},
	{"login", "����� � ���"},
	{"help", "������� ������� �� ��������"},
	{"quit", "������� ���"},
	{"", ""}
};

const CommandSpace LOCAL_COMMANDS[] = {		// ������������ ��������� ������ � �����������
	{"send", "��������� ���������"},
	{"read", "��������� ���������"},
	{"info", "������� ���������� � ������������"},
	{"delete", "������� ������� ������ ������������"},
	{"help", "������� ������� �� ��������"},
	{"logout", "����� �� ����"},
	{"", ""}
};

const int MIN_NAME_LENGTH = 2;	// ����������� ����� ����� ������������
const int MAX_NAME_LENGTH = 32;	// ������������ ����� ����� ������������
const int MIN_LOGIN_LENGTH = 2;	// ����������� ����� login
const int MAX_LOGIN_LENGTH = 16;	// ������������ ����� login
const int MIN_PASSWORD_LENGTH = 3;	// ����������� ����� ������
const int MAX_PASSWORD_LENGTH = 8;	// ������������ ����� ������
const int INITIAL_COUNT = 2;	// ��������� ����� ������� � ������� �������������; ����������� ��������=2 ������ ������ ��� ������������!!
const int INITIAL_MSG_COUNT = 2;	// ��������� ����� ������� � �����������; ����������� ��������=2 ������ ������ ��� ������������!!
const char SERVICE_NAME[] = {"��� ������������" };	// ��� ���������� ������������ � �������� 0
const char SERVICE_LOGIN[] = {"all"};	// login ���������� ������������ � �������� 0
const char USER_DATA_FILE_NAME[] = {"users.json"};	// ��� ����� ��� �������� ������ �������������
const char MSG_DATA_FILE_NAME[] = {"msgs.json"};	// ��� ����� ��� �������� ���������
const char SEPARATOR[] = {"-------------------------------------------------------------------------\n"};
const char DATE_TIME_FORMAT[] = {"[%Y-%m-%d %H:%M:%S]"};