#pragma once
#include <iostream>
#include "Student.h"
#include <random>

using namespace std;
class StudentMenu
{
public : 
	Student student;
	string selectedCategory;
	string loginId, password;

	int totalQuestions = 0; // Total questions in the exam
	int correctAnswers = 0; // Count of correct answers
	StudentMenu() {
		student.Load();
	}
	void DisplayMenu();
	void ExamMenu();

	void TakeExam();
	void ViewCategories();
	void ViewExamResults();

	void Register();
	bool Login();
};

