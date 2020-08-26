#pragma once
#include "Person.h"
class StatisticsManager {
 private:
  Person p;

 public:
  StatisticsManager(const Person& user);
  void ShowStats();
};
