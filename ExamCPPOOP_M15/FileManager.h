#pragma once
#include <iostream>
#include <fstream>
#include "ExamRecord.h"
#include "json.hpp"
#include "Test.h"
using json = nlohmann::json;
using namespace std;
class FileManager
{
public : 
	string path = "users.json";

	void SaveUserInformationDataJson(json json);
	json LoadUserInformationDataJson();

	void SaveExamRecord(vector<ExamRecord> records);
	void LoadExamRecord(vector<ExamRecord> records);
		
	void saveTests(const vector<Test>& tests, const string& filename);
	void loadTests(vector<Test>& tests, const string& filename);
};

