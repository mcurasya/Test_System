#pragma once

#include <iostream>
#include <string>
struct FullName {
  std::string first;
  std::string last;
  std::string middle;
};

class Person {
 protected:
  std::string login;
  FullName name;
  std::string address;
  std::string phone;
  bool isAdmin;
 public:
  std::string getLogin() const;
  bool getIsAdmin() const;
  Person(std::string login);
  Person();
  ~Person();
};

std::istream& operator>>(std::istream& is, FullName& name);
std::ostream& operator<<(std::ostream& is, const FullName& name);