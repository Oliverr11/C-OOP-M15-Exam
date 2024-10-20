#pragma once
#include <iostream>
#include <fstream>
#include "Test.h"
#include "Student.h"
#include "User.h"
#include "FileManager.h"
using namespace std;
class Admin
{
public : 

	vector<Test> tests;
	string fileName = "tests.json";
	bool Login(string loginId, string loginpassword);
	FileManager fm;
	Student student;
	Admin() {
		fm.loadTests(tests,fileName);
	}

	//modify user
	void CreateAccount(string RegisterID, string RegisterPassword, string fullname, string address, string phone);
	void DeleteAccount(string userName);
	bool DeleteExamRecords(string username);
	void ChangeUserInformation(string userName);

	void UpdateExamRecords(string oldID, string newID, string oldName, string newName);
	

	void addCategory(string category);
	void addQuestionToCategory(int testIndex, string questionText, const vector<string> options, int correctAnswer);
	void deleteCategory(int testIndex);
	void deleteQuestionFromCategory(int testIndex, int questionIndex);

	void displayCategories();

	void addExamRecord(string studentId,string category, string name, int score);
	void loadExamRecords(vector<ExamRecord>& records);

	json toJson();
	void fromjson(json j);
};

