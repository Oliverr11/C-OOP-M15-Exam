#pragma once
#include <iostream>
#include "Admin.h"
#include "Student.h"
#include "FileManager.h"
using namespace std;
class AdminMenu
{
public : 
	
	Admin admin;
	Student student;
	void MainMenu();
	void ModifyUserMenu();
	void ManageTestMenu();
	//modify user
	void CreateAccount();
	void DeleteAccount();
	void ChangeUserInformation();

	//manage test
	void AddCategory();
	void AddQuestionCategory();
	void DeleteCategory();
	void DeleteQuestionFromCategory();

	void displayCategories();

	void Login();
	
};

