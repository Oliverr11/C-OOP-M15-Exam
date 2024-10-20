#pragma once
#include <iostream>
#include <vector>
#include "json.hpp" 
#include <fstream>
using json = nlohmann::json;
using namespace std;
class ExamRecord
{
public : 
	string studentID;
	string studentName; 
	string category;
	int score;
	ExamRecord() = default;
	ExamRecord(string id , string category , string studentName,int score);

	json toJson();
	ExamRecord fromJson(json j);
};

