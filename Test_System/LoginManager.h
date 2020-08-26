#pragma once
#include "Person.h"
#include "Defines.h"
class LoginManager
{
private:
	Person Login();
	Person RegisterAdmin();
public:
	Person Register();
	LoginManager();
	~LoginManager();
	Person LoginOrRegister();
};
