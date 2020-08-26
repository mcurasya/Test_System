#include "LoginManager.h"

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include "Defines.h"
#include "Utility.h"


Person LoginManager::Login() {
  std::map<std::string, std::string> loginToPassword;
  GetLoginPasswords(loginToPassword);

  while (true) {
    std::string login;
    std::string password;
    std::cout << "login >>> ";
    std::cin >> login;
    std::cout << "password >>> ";
    std::cin >> password;
    if (loginToPassword.count(login) && loginToPassword.at(login) == password) {
      std::string isAdmin;
      std::ifstream userFile(CreateUserFilepath(login));
      userFile >> isAdmin >> isAdmin;
      userFile.close();
      return Person(login);
    }
    std::cout
        << "sorry, such user doesnt exist or a password is wrong, try again"
        << std::endl;
  }
}

Person LoginManager::Register() {
  std::string login;
  std::map<std::string, std::string> loginToPassword;
  GetLoginPasswords(loginToPassword);
  while (true) {
    std::cout << "enter new login >>> ";
    std::cin >> login;
    if (loginToPassword.count(login)) {
      std::cout << "sorry, such user already exists, try again\n";
    } else {
      break;
    }
  }
#ifdef _WIN32
  std::ostringstream login_filepath_stream;
  login_filepath_stream << DATABASE_FOLDER << "\\" << LOGIN_PASSWORD_FILE;
#else
  std::ostringstream login_filepath_stream;
  login_filepath_stream << DATABASE_FOLDER << "/" << LOGIN_PASSWORD_FILE;
#endif

  std::ofstream loginFile(login_filepath_stream.str(), std::ios::app);
  std::string password;
  std::string first_name, last_name, middle_name;
  std::string phone;
  std::string address;
  std::ostringstream os;
  os << "isAdmin false" << std::endl;
  std::cout << "enter full name (format: last first middle) >>> ";
  std::cin >> last_name >> first_name >> middle_name;
  os << "Name " << last_name << " " << first_name << " " << middle_name
     << std::endl;
  std::cout << "enter address >>> ";
  std::cin >> address;
  os << "Adress " << address << std::endl;
  std::cout << "enter phone >>> ";
  std::cin >> phone;
  std::cout << "enter password >>> ";
  std::cin >> password;
  loginFile << login << " " << password << std::endl;
  os << "Phone " << phone << std::endl;
  std::ostringstream folder_os;
  folder_os << "mkdir " << DATABASE_FOLDER << "\\" << USERS_FOLDER << "\\"
            << login;
  system(folder_os.str().c_str());
  std::ofstream user_stream(CreateUserFilepath(login));
  user_stream << os.str();
  user_stream.close();
  loginFile.close();
  return Person(login);
}

Person LoginManager::RegisterAdmin() {
  std::string login;
  std::map<std::string, std::string> loginToPassword;
  GetLoginPasswords(loginToPassword);
  while (true) {
    std::cout << "enter new login >>> ";
    std::cin >> login;
    if (loginToPassword.count(login)) {
      std::cout << "sorry, such user already exists, try again\n";
    } else {
      break;
    }
  }
#ifdef _WIN32
  std::ostringstream login_filepath_stream;
  login_filepath_stream << DATABASE_FOLDER << "\\" << LOGIN_PASSWORD_FILE;
#else
  std::ostringstream login_filepath_stream;
  login_filepath_stream << DATABASE_FOLDER << "/" << LOGIN_PASSWORD_FILE;
#endif

  std::ofstream loginFile(login_filepath_stream.str(), std::ios::app);
  std::string password;
  std::string first_name, last_name, middle_name;
  std::string phone;
  std::string address;
  std::ostringstream os;
  os << "isAdmin true" << std::endl;
  std::cout << "enter full name (format: last first middle) >>> ";
  std::cin >> last_name >> first_name >> middle_name;
  os << "Name " << last_name << " " << first_name << " " << middle_name
     << std::endl;
  std::cout << "enter address >>> ";
  std::cin >> address;
  os << "Adress " << address << std::endl;
  std::cout << "enter phone >>> ";
  std::cin >> phone;
  std::cout << "enter password >>> ";
  std::cin >> password;
  loginFile << login << " " << password << std::endl;
  os << "Phone " << phone << std::endl;
  std::ostringstream folder_os;
  folder_os << "mkdir " << DATABASE_FOLDER << "\\" << USERS_FOLDER << "\\"
            << login;
  system(folder_os.str().c_str());
  std::ofstream user_stream(CreateUserFilepath(login));
  user_stream << os.str();
  user_stream.close();
  loginFile.close();
  return Person(login);
}

LoginManager::LoginManager() {}

LoginManager::~LoginManager() {}

Person LoginManager::LoginOrRegister() {
  if (!std::experimental::filesystem::exists(DATABASE_FOLDER)) {
    std::ostringstream os;
    os << "mkdir " << DATABASE_FOLDER << " & cd " << DATABASE_FOLDER
       << " & mkdir " << USERS_FOLDER << " & mkdir " << TESTS_FOLDER
       << " & cd ..";
    system(os.str().c_str());

    return RegisterAdmin();
  }
  while (true) {
    std::cout << "Hello, do you want to register(1) or login(2)? >> ";
    std::string operation;
    std::cin >> operation;
    if (operation == "login" || operation == "2") {
      return Login();
    } else if (operation == "register" || operation == "1") {
      return Register();
    }
  }
}
