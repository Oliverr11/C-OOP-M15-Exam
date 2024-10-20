#pragma once
#include <iostream>
#include <vector>
#include "json.hpp"
using nlohmann::json;
using namespace std;
class Question
{
public :
	string questionText;
	vector<string> options;
	int correctAnswer;
	Question() = default;

	Question(string questionText, vector<string> opts, int answer);
	json toJson();
	Question fromJson(json j);
};

