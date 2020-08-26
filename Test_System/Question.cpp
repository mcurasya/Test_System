#include "Question.h"
#include <fstream>
#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& os, const Question& question) {
  os << question.getQuestionText() << std::endl;
  auto answers = question.getAnswers();
  for (size_t i = 0; i < answers.size(); i++) {
    os << i + 1 << answers[i] << std::endl;
  }
  return os;
}

std::istream& operator>>(std::istream& is, Question& question) {
  std::string q;
  std::vector<std::string> answers;
  int correct;

  int answerCount;
  std::getline(is, q);
  is >> answerCount;

  for (size_t i = 0; i < answerCount; i++) {
    std::string answer;
    std::getline(is, answer);
    answers.push_back(answer);
  }
  is >> correct;
  question = {q, answers, correct};
  return is;
}

std::string Question::getQuestionText() const {
  return questionText;
}

std::vector<std::string> Question::getAnswers() const {
  return answers;
}

bool Question::CheckIfCorrect(int answer) const {
  return answer == correctAnswer;
}

Question::Question(std::string text,
                   const std::vector<std::string>& answers,
                   int correct) {
  questionText = text;
  this->answers = answers;
  correctAnswer = correct;
}

Question::Question() {}

void Question::Dump(std::ofstream& stream) {
  stream << questionText << std::endl << answers.size() << std::endl;
  for (const auto& answer : answers) {
    std::cout << answer << std::endl;
  }
  std::cout << correctAnswer << std::endl << std::endl;

}
