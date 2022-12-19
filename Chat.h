#pragma once
#include <string>
//#include <cstdlib>
//#include <windows.h>
#include "Users.h"
#include "Messages.h"
#include "Constants.h"


void print_help(const CommandSpace* _commandSpace);	// ������ ������� �� ��������
void AtStart();	// ��������� ���������
int _get_command(const CommandSpace* _commandSpace);	// ��������� ������� � �������, ������ ��������������� ���� ��������
int get_command(const CommandSpace* _commandSpace);	// ��������� ������� � �������, ������ ��������������� ���� ��������
int get_command(const std::string& _str, const CommandSpace* _commandSpace);	// ��������� ������� � �������, ������ ��������������� ���� ��������
int Chat(Users& _users, Messages& _messages);
