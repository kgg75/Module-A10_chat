#pragma once
#include <iostream>
#include <string>
#include "Users.h"


void lowercase(std::string& _str);	// �������������� ������ � ������ �������
std::string lowercase_s(const std::string& _str);	// �������������� ������ � ������ �������
bool check_empty_name(const std::string& _str, const std::string& _subject);	// �������� ������ �� �������
bool check_spaces(const std::string& _str, const std::string& _subject);	// �������� ������ �� �������
bool check_name(const std::string& _str, const std::string& _subject, const int& _minLength, const int& _maxLength);	// �������� ������ �� �������, �����������/������������ �����
std::string get_value_from_console();	// ��������� �������� � �������
std::string get_string_from_console();	// ��������� ������ � ������� � � ������� �� ��������� � �������� ��������
std::string GetTime();	// ��������� �������� �������
bool QuestionYN(const std::string& _str);	// ������ � ����� ���������� ������ (��/���)