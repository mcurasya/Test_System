
#include <sstream>
#include <string>
#include <fstream>
#include "Defines.h"
#include "Utility.h"

std::string CreateUserFilepath(std::string login) {
#ifdef _WIN32
  std::ostringstream filepath_stream;
  filepath_stream << DATABASE_FOLDER << "\\" << USERS_FOLDER << "\\" << login << "\\" << login
                  << USER_FILE_FORMAT;
#else
  std::ostringstream filepath_stream;
  filepath_stream << DATABASE_FOLDER << "/" << USERS_FOLDER << "/" << login
                  << "/"
                  << login
                  << USER_FILE_FORMAT;
#endif
  return filepath_stream.str();
}

void GetLoginPasswords(std::map<std::string, std::string>& result) {
#ifdef _WIN32
  std::ostringstream filepath_stream;
  filepath_stream << DATABASE_FOLDER << "\\" << LOGIN_PASSWORD_FILE;
#else
  std::ostringstream filepath_stream;
  filepath_stream << DATABASE_FOLDER << "/" << LOGIN_PASSWORD_FILE;
#endif
  std::string filepath = filepath_stream.str();
  std::ifstream loginFile(filepath);
  std::string login;
  std::string passwd;
  while (loginFile) {
    loginFile >> login >> passwd;
    result[login] = passwd;
  }
  loginFile.close();
}
