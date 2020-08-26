#pragma once

#include "Person.h"

enum class Mode {
  USER,
  ADMIN
};

enum class Action {
  DO_NEW_TEST,
  CONTINUE_TEST,
  SHOW_RESULT,

  ADD_USER,
  CHANGE_USER,
  DELETE_USER,
  SHOW_STATS,
  ADD_CATEGORY,
  ADD_TEST,
  ADD_QUESTION,

  EXIT,
  WRONG_ACTION

};

class MainMenuManager {
 private:
  Person currentUser;
  Mode userMode;
  void ShowActions();
  Action getAction();
  bool doAction(Action a);
 public:
  MainMenuManager(Person user);
  void Run();
};
