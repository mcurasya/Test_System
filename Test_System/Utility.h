#pragma once
#include <string>
#include <map>
std::string CreateUserFilepath(std::string login);
void GetLoginPasswords(std::map<std::string, std::string>& result);