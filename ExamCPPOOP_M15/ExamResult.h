#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
class ExamResult
{
public  :

    string studentName; // Student's name
    string category;
    double score;
    int correctAnswers;
    int totalQuestions;

    ExamResult() = default;
    ExamResult(string name, string category, double score, int correct, int total);
    void SaveExamRecord();

    json toJson();
    void fromJson(json j);
    //ExamResult fromJson(json j);
};

