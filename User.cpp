#include <iostream>
#include "User.h"


User::User(const int _id,
	const std::string _name,
	const std::string _login,
	const std::string _password,
	const bool _locked,
	const bool _logged)
	:
	id(_id),
	name(_name),
	login(_login),
	password(_password),
	locked(_locked),
	logged(_logged)
{}

