#pragma once
#include <iostream>
#include "Student.h"
using namespace std;
class MenuUser
{
public  :
	Student user;
	MenuUser() {
		user.Load();
	}
	
	void DisplayMenu();
	void Register();
	void Login();
};

