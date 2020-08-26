#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include "MainMenuManager.h"
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include "Defines.h"
#include "LoginManager.h"
#include "StatisticsManager.h"
#include "TestManager.h"
#include "Utility.h"

namespace fs = std::experimental::filesystem;

void ShowAdminActions() {
  std::cout << "1) Add new user" << std::endl
            << "2) Change user info" << std::endl
            << "3) Delete user" << std::endl
            << "4) Show statistics" << std::endl
            << "5) Add test category" << std::endl
            << "6) Add test" << std::endl
            << "7) Add question to test" << std::endl
            << "0) Exit" << std::endl;
}

void ShowUserActions() {
  std::cout << "1) Do new test" << std::endl
            << "2) Continue last test" << std::endl
            << "3) Show previous results" << std::endl
            << "0) Exit" << std::endl;
}

void MainMenuManager::ShowActions() {
  // system("cls");
  if (currentUser.getIsAdmin()) {
    ShowAdminActions();
  } else {
    ShowUserActions();
  }
}

Action GetAdminAction() {
  int op;
  std::cin >> op;
  switch (op) {
    case 1:
      return Action::ADD_USER;
    case 2:
      return Action::CHANGE_USER;
    case 3:
      return Action::DELETE_USER;
    case 4:
      return Action::SHOW_STATS;
    case 5:
      return Action::ADD_CATEGORY;
    case 6:
      return Action::ADD_TEST;
    case 7:
      return Action::ADD_QUESTION;
    case 0:
      return Action::EXIT;
    default:
      return Action::WRONG_ACTION;
  }
}

Action GetUserAction() {
  int op;
  std::cin >> op;
  switch (op) {
    case 1:
      return Action::DO_NEW_TEST;
    case 2:
      return Action::CONTINUE_TEST;
    case 3:
      return Action::SHOW_RESULT;
    case 0:
      return Action::EXIT;
    default:
      return Action::WRONG_ACTION;
  }
}

Action MainMenuManager::getAction() {
  std::cout << " >>> ";
  return currentUser.getIsAdmin() ? GetAdminAction() : GetUserAction();
}

void DeleteUser(std::string login) {
  std::map<std::string, std::string> loginToPass;
  GetLoginPasswords(loginToPass);
  if (!loginToPass.count(login)) {
    throw std::invalid_argument("such user does not exist");
  }
  loginToPass.erase(login);
  std::ostringstream login_filepath_stream;
  login_filepath_stream << DATABASE_FOLDER << "\\" << LOGIN_PASSWORD_FILE;
  std::ofstream fout(login_filepath_stream.str());
  for (auto record : loginToPass) {
    fout << record.first << " " << record.second << std::endl;
  }
  fout.close();
  std::ostringstream filepath_stream;
  filepath_stream << DATABASE_FOLDER << "\\" << USERS_FOLDER << "\\" << login;
  system(("rmdir /s /q " + filepath_stream.str()).c_str());
}

bool MainMenuManager::doAction(Action a) {
  TestManager tm(currentUser);
  StatisticsManager sm(currentUser);
  switch (a) {
    case Action::DO_NEW_TEST:
      tm.DoTest();
      break;
    case Action::CONTINUE_TEST:
      tm.ContinueTest();
      break;
    case Action::SHOW_RESULT:
      break;
    case Action::ADD_USER: {
      LoginManager lm;
      lm.Register();
    } break;
    case Action::CHANGE_USER: {
      std::string login;
      std::cout << "enter user you want to change >>> ";
      std::cin >> login;
      DeleteUser(login);
      LoginManager lm;
      lm.Register();
    } break;
    case Action::DELETE_USER: {
      std::string login;
      std::cout << "enter user you want to delete >>> ";
      std::cin >> login;
      DeleteUser(login);
    } break;
    case Action::SHOW_STATS:
      break;
    case Action::ADD_CATEGORY: {
      std::cout << "enter new category name >> ";
      std::string cat;
      std::cin >> cat;
      tm.AddCategory(cat);
    } break;
    case Action::ADD_TEST: {
      std::cout << "enter category name >> ";
      std::string cat;
      std::cin >> cat;
      tm.CreateTest(cat);
    } break;
    case Action::ADD_QUESTION: {
      std::cout << "enter category name >> ";
      std::string cat;
      std::cin >> cat;
      std::cout << "enter test name >> ";
      std::string test;
      std::cin >> test;
      tm.AddQuestion(cat, test);
    } break;
    case Action::EXIT:
      return false;
    case Action::WRONG_ACTION:
      break;
    default:
      break;
  }
  return true;
}

MainMenuManager::MainMenuManager(Person user) {
  currentUser = user;
  userMode = user.getIsAdmin() ? Mode::ADMIN : Mode::USER;
}

void MainMenuManager::Run() {
  bool running = true;
  while (running) {
    try {
      ShowActions();
      Action action = getAction();
      running = doAction(action);
    } catch (std::exception& e) {
      std::cout << "sorry error occured " << e.what()
                << "please press any key to continue" << std::endl;
    }
  }
}
