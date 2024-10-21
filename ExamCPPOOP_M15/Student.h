#pragma once
#include <iostream>
#include <vector>
#include "FileManager.h"
#include "Test.h"
#include "User.h";
using namespace std;
class Student : public User
{
public : 
	Student() {
		Load();
		}
	vector<User> users;

	FileManager filemanager;

	void Register(string RegisterID, string RegisterPassword, string fullname, string address, string phone);
	bool Login(string LoginId, string LoginPassword);
	bool DeleteStudent(string username);
	void UpdateUserID(string username, string newID);
	void UpdateUserPassword(string username, string newPassword);
	void UpdateUserFullName(string username, string newFullName);
	void UpdateUserAddress(string username, string newAddress);
	void UpdateUserPhone(string username, string newPhone);


	void TakeExam(string category);
	void ViewExamResults();


	bool UserExists(string username);


	void Save();
	void Load();

	User* FindDiplicateName(string RegisterID);
	User* FindUserToLogin(string LoginId, string LoginPassword);
};

