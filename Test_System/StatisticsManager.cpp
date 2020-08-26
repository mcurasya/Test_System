#include "StatisticsManager.h"
#include <sstream>
#include <fstream>
#include "Defines.h"
StatisticsManager::StatisticsManager(const Person& user) {
  p = user;
}

void StatisticsManager::ShowStats() {
  std::ostringstream os;  // path to user statistics
  os << DATABASE_FOLDER << "\\" << USERS_FOLDER << "\\" << p.getLogin() << "\\"
     << p.getLogin() << STATISTICS_FILE_FORMAT;
  std::ifstream fin(os.str());
  int sum = 0; 
  int count = 0;
  while (fin) {
    std::string category;
    std::string test;
    char separatop;
    int res;
    int allQuestions;
    int mark;
    fin >> category >> test >> res >> separatop >> allQuestions >> mark;
    std::cout << "category " << category << " test " << test << ": " << res
              << separatop << allQuestions << " mark: " << mark <<std::endl;
    sum += mark;
    count++;
  }
  std::cout << "average: " << static_cast<double>(sum) / count << std::endl;
}
