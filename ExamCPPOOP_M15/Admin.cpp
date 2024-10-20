#include "Admin.h"

bool Admin::Login(string loginId, string loginpassword)
{
    ifstream inputFile("admin.json");
    if (!inputFile.is_open()) {
        cout << "Error opening file." << std::endl;
        return false;
    }
    else {
        json accountData;
        inputFile >> accountData;
        inputFile.close();

        string storedUsername = accountData["id"];
        string storedPassword = accountData["password"];
        return (loginId == storedUsername && loginpassword == storedPassword);
    }
}

void Admin::addCategory(string category)
{

    Test newTest(category);
    newTest.questions = {};
    tests.push_back(newTest);   
    cout << "Category added: " << category << endl; 
    fm.saveTests(tests,fileName);
}

void Admin::addQuestionToCategory(int testIndex, string questionText, const vector<string> options, int correctAnswer)
{

    if (testIndex < 0 || testIndex >= tests.size()) {
        throw out_of_range("Test index is out of range.");
    }
    tests[testIndex].addQuestion(questionText, options, correctAnswer);
    cout << "Question added successfully!" << endl;
    fm.saveTests(tests, fileName);
}

void Admin::deleteCategory(int testIndex)
{
    if (testIndex < 0 || testIndex >= tests.size()) {
        throw out_of_range("Test index is out of range.");
    }
    tests.erase(tests.begin() + testIndex); // Remove the category at the specified index
    fm.saveTests(tests, fileName); // Save the updated tests to the file
    cout << "Category deleted successfully!" << endl;
}

void Admin::deleteQuestionFromCategory(int testIndex, int questionIndex)
{
    if (testIndex < 0 || testIndex >= tests.size()) {
        throw out_of_range("Test index is out of range.");
    }
    if (questionIndex < 0 || questionIndex >= tests[testIndex].questions.size()) {
        throw out_of_range("Question index is out of range.");
    }
    tests[testIndex].questions.erase(tests[testIndex].questions.begin() + questionIndex); // Remove the question
    fm.saveTests(tests, fileName); // Save the updated tests to the file
    cout << "Question deleted successfully!" << endl;
}

void Admin::displayCategories()
{
    cout << "Available Categories:" << endl;
    for (int i = 0; i < tests.size(); ++i) {
        cout << i + 1 << ": " << tests[i].category << endl;
    }
}

void Admin::addExamRecord(const string& studentId, const string& name, int score)
{
    ExamRecord newRecord(studentId, name, score);
    vector<ExamRecord> records;
    fm.LoadExamRecord(records); // Load existing records
    records.push_back(newRecord);
    fm.SaveExamRecord(records);
    cout << "Exam record added for " << name << " with score: " << score << endl;
}

void Admin::loadExamRecords(vector<ExamRecord>& records)
{
    fm.LoadExamRecord(records);
    cout << "Exam records loaded." << endl;
}




json Admin::toJson()
{
    json j;
    for (auto& test : tests) {
        j.push_back(test.toJson());
    }
    return j;
}

void Admin::fromjson(json j)
{
    Test t;
    for (auto cateJson : j) {
        tests.push_back(t.fromJson(cateJson));
    }
}

