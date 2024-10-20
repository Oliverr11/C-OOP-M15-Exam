#pragma once
#include <iostream>
#include <fstream>
#include "Test.h"
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
	Admin() {
		fm.loadTests(tests,fileName);
	}


	void addCategory(string category);
	void addQuestionToCategory(int testIndex, string questionText, const vector<string> options, int correctAnswer);
	
	void deleteCategory(int testIndex);
	void deleteQuestionFromCategory(int testIndex, int questionIndex);

	void displayCategories();

	void addExamRecord(const string& studentId, const string& category, int score);
	void loadExamRecords(vector<ExamRecord>& records);

	json toJson();
	void fromjson(json j);
};

