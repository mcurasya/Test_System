#pragma once
#include <string>
#include <vector>
#include "Person.h"
#include "Question.h"
class Test {
 private:
  Person p;
  std::vector<Question> questions;
  std::string cat;
  std::string filename;
  int correctAnswers;
  int answersCount;
  int currentQuestion;
  void SaveStatus();
  void Tick();

 public:
  Test(std::string category, std::string test_filename, const Person& tested);
  ~Test();
  void Run();
  static Test LoadUnfinishedTest(const Person& user);

  std::vector<Question> getQuestions() const;
  std::string getCategory() const;
  std::string getFilename() const;
};
std::ostream& operator<<(std::ostream& os, const Test& t);