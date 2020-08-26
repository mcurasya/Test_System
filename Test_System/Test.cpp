#include "Test.h"
#include <fstream>
#include <sstream>
#include "Defines.h"

void Test::SaveStatus() {
  std::ostringstream os;
  os << DATABASE_FOLDER << "\\" << USERS_FOLDER << "\\" << p.getLogin() << "\\"
     << UNFINISHED_TEST_FILE;
  std::ofstream fout(os.str());
  fout << cat << " " << filename << std::endl;
  fout << currentQuestion << std::endl << correctAnswers;
  fout.close();
}

void Test::Tick() {
  std::cout << "Question " << currentQuestion + 1 << std::endl;
  std::cout << questions[currentQuestion] << std::endl;
  std::cout << " >> ";
  int answer;
  std::cin >> answer;
  correctAnswers += questions[currentQuestion].CheckIfCorrect(answer);
  currentQuestion++;
}

Test::Test(std::string category,
           std::string test_filename,
           const Person& tested) {
  cat = category;
  filename = test_filename;
  correctAnswers = 0;
  currentQuestion = 0;
  std::ostringstream os;
  os << DATABASE_FOLDER << "\\" << TESTS_FOLDER << "\\" << category << "\\"
     << test_filename << TEST_FILE_FORMAT;
  std::ifstream fin(os.str());
  std::string placeholder;
  fin >> placeholder >> placeholder;
  while (fin) {
    Question q;
    fin >> q;
    questions.push_back(q);
  }
  answersCount = questions.size();
  p = tested;
}

Test::~Test() {}

void Test::Run() {
  for (int i = currentQuestion; i < answersCount; i++) {
    Tick();
    SaveStatus();
  }
  std::cout << "test finished you have " << correctAnswers << "/"
            << answersCount << "right answers, your score is "
            << correctAnswers / answersCount * 12;
  std::ostringstream os;
  os << DATABASE_FOLDER << "\\" << USERS_FOLDER << "\\" << p.getLogin() << "\\"
     << p.getLogin() << STATISTICS_FILE_FORMAT;
  std::ofstream fout(os.str(), std::ios::app);
  fout << cat << " " << filename << " " << correctAnswers << "/" << answersCount
       << " " << correctAnswers / answersCount * 12 << std::endl;
  fout.close();
}

Test Test::LoadUnfinishedTest(const Person& user) {
  std::ostringstream os;
  os << DATABASE_FOLDER << "\\" << USERS_FOLDER << "\\" << user.getLogin()
     << "\\" << UNFINISHED_TEST_FILE;
  std::ifstream fin(os.str());
  if (!fin) {
    throw std::logic_error("sorry, you have finished all your tests");
  }
  std::string category;
  std::string filename;
  fin >> category >> filename;
  Test t(category, filename, user);
  fin >> t.currentQuestion >> t.correctAnswers;
  fin.close();
  return t;
}

std::vector<Question> Test::getQuestions() const {
  return questions;
}

std::string Test::getCategory() const {
  return cat;
}

std::string Test::getFilename() const {
  return filename;
}

std::ostream& operator<<(std::ostream& os, const Test& t) {
  os << t.getCategory() << " " << t.getFilename() << std::endl << std::endl;
  for (auto q : t.getQuestions()) {
    os << q << std::endl;
  }
  return os;
}
