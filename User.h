#pragma once
#include <string>


struct User {
	int id;	// ���������� �������������
	std::string name;	// ������ ���
	std::string login;	// ������� ��� (login)
	std::string password;	// ������
	bool locked = false;	// ���� ���������� ������������ (��������������)
	bool logged = false;	// ����, ����������� �� ���� ������������

	User(const int id,
		const std::string name,
		const std::string login,
		const std::string password,
		const bool locked = false,
		const bool logged = false);
};

