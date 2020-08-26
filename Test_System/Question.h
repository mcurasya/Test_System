#pragma once
#include <iostream>
#include <vector>
class Question {
 private:
  std::string questionText;
  std::vector<std::string> answers;
  int correctAnswer;

 public:
  std::string getQuestionText() const;
  std::vector<std::string> getAnswers() const;
  bool CheckIfCorrect(int answer) const;
  Question(std::string text, const std::vector<std::string>& answers, int correct);
  Question();
  void Dump(std::ofstream& stream);
};

std::ostream& operator<<(std::ostream& os, const Question& question);
std::istream& operator>>(std::istream& is, Question& question);