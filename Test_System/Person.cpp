#include "Person.h"

#include <fstream>
#include <sstream>
#include "Defines.h"
#include "Utility.h"

std::string Person::getLogin() const {
  return login;
}

bool Person::getIsAdmin() const {
  return isAdmin;
}

Person::Person(std::string login) {
  std::ifstream fin(CreateUserFilepath(login));
  this->login = login;
  std::string placeholder;
  std::string isAdmin;
  fin >> placeholder >> isAdmin;
  fin >> placeholder >> name;
  fin >> placeholder >> address;
  fin >> placeholder >> phone;
  this->isAdmin = (isAdmin == "true");
  fin.close();
}

Person::Person() {}

Person::~Person() {}

std::istream& operator>>(std::istream& is, FullName& name) {
  is >> name.last >> name.first >> name.middle;
  return is;
}

std::ostream& operator<<(std::ostream& os, const FullName& name) {
  os << name.last << " " << name.first << " " << name.middle;
  return os;
}
