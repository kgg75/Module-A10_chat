#pragma once
#include <string>
#include <vector>
#include "User.h"

class Users {
	private:
		std::vector<User> user;	// ������ � ������� �������������
		int usersCount = 0;	// ���������� �������������
		int idsCount = 0; // ���������� �������������� ���������������
		int currentUser = idsCount; // ���������� ����� �������� ������������ (���������� � 1)
		bool isChanged = false;	// ���� ������� ��������� � ������ �������������
		int FindLogin(const std::string& _login);	// �������� ������������ ��������� login ������������; ������� ����������� ������ � ������ ������
		void CheckArraySize();	// �������� ������� ���������� ����� � ������� � ��� ���������� ��� �������������
	public:
		Users();
		//~Users();
		bool NewUser();	// ����������� ������ ������������
		bool Login();	// ���� ������������ � ���
		void Logout();	// ����� ������������ �� ����
		int ChooseUser();	// ����� ���������� ��� �������� ���������; ���������� id ������������
		bool Open();	// ������ ������ ������������� �� �������� �����
		bool Save();	// ���������� ������ ������������� �� ������� ����
		bool DeleteUser();	// �������� ������� ������ ������������
		void Show();	// ����������� ������ �������� ������������
		void Show(const int _user_index);	// ����������� ������ ���������� ������������
		// getters
		int GetCurrentUser() const;	// ���������� ����� �������� ������������
		int GetUserId() const;	// id �������� ������������
		int GetUserId(const int _user_index) const;	// id ���������� ������������
		std::string GetUserLogin() const;	// login �������� ������������
		std::string GetUserLogin(const int _id) const;	// login ���������� ������������
		bool GetIsChanged() const;	// ������� ����� ������� ��������� � ������ �������������
};

