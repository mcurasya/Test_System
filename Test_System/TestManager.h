#pragma once
#include <string>
#include "Person.h"
#include "Test.h"
class TestManager {
 private:
  Person p;

 public:
  TestManager(const Person& p);
  ~TestManager();
  void AddCategory(std::string category);
  void CreateTest(std::string category);
  void AddQuestion(std::string category, std::string test);
  void DoTest();
  void ContinueTest();
};
