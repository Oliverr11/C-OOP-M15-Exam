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
	string category;
	int score;
	ExamRecord() = default;
	ExamRecord(string id , string category ,int score);

	json toJson();
	ExamRecord fromJson(json j);
};

