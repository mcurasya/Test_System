#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "TestManager.h"
#include <experimental/filesystem>
#include <fstream>
#include <sstream>
#include "Defines.h"
#include "Question.h"

namespace fs = std::experimental::filesystem;

TestManager::TestManager(const Person& p) {
  this->p = p;
}

TestManager::~TestManager() {}

void TestManager::AddCategory(std::string category) {
  std::ostringstream os;
  os << DATABASE_FOLDER << "\\" << TESTS_FOLDER << "\\" << category;
  if (fs::exists(os.str())) {
    throw std::logic_error("sorry, such category already exists");
  }
  fs::create_directory(os.str());
  std::cout << "directory created" << std::endl;
}

void TestManager::CreateTest(std::string category) {
  std::string test;
  std::cout << "enter test name >> ";
  std::cin >> test;
  std::ostringstream cat_stream;
  cat_stream << DATABASE_FOLDER << "\\" << TESTS_FOLDER << "\\" << category;
  std::ostringstream os;
  os << DATABASE_FOLDER << "\\" << TESTS_FOLDER << "\\" << category << "\\"
     << test << TEST_FILE_FORMAT;
  if (fs::exists(os.str())) {
    throw std::logic_error("sorry, such test already exists");
  }
  if (!fs::exists(cat_stream.str())) {
    throw std::logic_error("sorry, such category does not exist");
  }
  std::ofstream fout(os.str());
  fout << category << " " << test << std::endl << std::endl;
  fout.close();
  std::cout << "enter question count >> ";
  int count;
  std::cin >> count;
  for (size_t i = 0; i < count; i++) {
    AddQuestion(category, test);
  }
}

void TestManager::AddQuestion(std::string category, std::string test) {
  std::ostringstream os;
  os << DATABASE_FOLDER << "\\" << TESTS_FOLDER << "\\" << category << "\\"
     << test << TEST_FILE_FORMAT;
  if (!fs::exists(os.str())) {
    throw std::logic_error("sorry, such test does not exist");
  }
  std::cout << "enter question\n >>> ";
  std::string q;
  do {
    std::getline(std::cin, q);
  } while (q == "");
  std::cout << "enter amount of answers >>> ";
  std::vector<std::string> answers;
  int count;
  std::cin >> count;
  for (size_t i = 0; i < count; i++) {
    std::cout << "enter answer >>> ";
    std::string answer;
    do {
      std::getline(std::cin, answer);
    } while (answer == "");
    answers.push_back(answer);
  }
  std::cout << "enter number of correct answer >>> ";
  int correct;
  std::cin >> correct;

  std::ofstream fout(os.str(), std::ios::app);
  Question question(q, answers, correct);
  question.Dump(fout);
  fout.close();
}

void TestManager::DoTest() {
  std::cout << "enter category >> ";
  std::string cat;
  std::cin >> cat;
  std::cout << "enter testname >>";
  std::string test;
  std::cin >> test;
  std::ostringstream cat_stream;
  cat_stream << DATABASE_FOLDER << "\\" << TESTS_FOLDER << "\\" << cat;
  std::ostringstream os;
  os << DATABASE_FOLDER << "\\" << TESTS_FOLDER << "\\" << cat << "\\" << test
     << TEST_FILE_FORMAT;
  if (!fs::exists(os.str())) {
    throw std::logic_error("sorry, such test does not exist");
  }
  if (!fs::exists(cat_stream.str())) {
    throw std::logic_error("sorry, such category does not exist");
  }
  Test t(cat, test, p);
  t.Run();
}

void TestManager::ContinueTest() {
  Test t = Test::LoadUnfinishedTest(p);
  t.Run();
}
