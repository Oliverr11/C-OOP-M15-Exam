#include "StudentMenu.h"

void StudentMenu::DisplayMenu()
{
    cout << "============= WELCOME =============" << endl;
    cout << "1. Register " << endl;
    cout << "2. Login " << endl;
    int opt;
    cout << "Enter Option : "; cin >> opt;
    switch (opt)
    {
    case 1:
        Register();
        break;
    case 2:
        Login();
        break;
    default:
        break;
    }
}

void StudentMenu::ExamMenu()
{
    cout << "================= IT-STEP Exam =================" << endl;
    cout << "1. View Categories" << endl;
    cout << "2. Take a Test" << endl;
    cout << "3. View Exam Results" << endl;
    cout << "4. Exit" << endl;

    int opt;
    cout << "Enter Option: ";
    cin >> opt;

    switch (opt) {
    case 1:
        ViewCategories();
        break;
    case 2:
        TakeExam();
        break;
    case 3:
        ViewExamResults();
        break;
    case 4:
        cout << "Exiting..." << endl;
        break;
    default:
        cout << "Invalid option. Please try again." << endl;
        ExamMenu(); 
        break;
    }   
}
void StudentMenu::TakeExam()
{
    string category;
    cout << "Enter the exam category you want to take: ";
    cin >> category;

    ifstream file("tests.json");
    if (!file.is_open()) {
        cout << "Error opening tests.json!" << endl;
        return;
    }

    json tests;
    file >> tests;

    json selectedCategory;
    bool categoryFound = false;

    for (const auto& test : tests) {
        if (test["category"] == category) {
            selectedCategory = test["questions"];
            categoryFound = true;
            break;
        }
    }

    if (!categoryFound) {
        cout << "Category not found." << endl;
        ExamMenu();
        return;
    }

    // Load the exam state if it exists
    int currentIndex = 0;
    int score = 0;
    ifstream stateFile("exam_state.json");

    if (stateFile.is_open()) {
        json state;
        stateFile >> state;
        currentIndex = state["currentIndex"].get<int>();
        score = state["score"].get<int>();
        stateFile.close();
    }

    int questionCount = min(static_cast<int>(selectedCategory.size()), 12);
    int maxQuestions = questionCount - currentIndex;

    for (int i = currentIndex; i < questionCount && i < currentIndex + maxQuestions; ++i) {
        const auto& question = selectedCategory[i];
        cout << question["questionText"] << endl;

        for (size_t j = 0; j < question["options"].size(); ++j) {
            cout << j + 1 << ". " << question["options"][j] << endl;
        }

        cout << "Enter your answer (1-" << question["options"].size() << "): ";
        int answer;
        cin >> answer;

        if (answer < 1 || answer > question["options"].size()) {
            cout << "Invalid answer! Please enter a number between 1 and " << question["options"].size() << "." << endl;
            continue;
        }

        int correctIndex = question["correctAnswer"].get<int>();
        if (answer - 1 == correctIndex) {
            cout << "Correct!" << endl;
            score++;
        }
        else {
            cout << "Incorrect! The correct answer was: " << question["options"][correctIndex] << endl;
        }

        // Save state after each question
        json state;
        state["currentIndex"] = i + 1; 
        state["score"] = score;

        ofstream stateOut("exam_state.json");
        if (stateOut.is_open()) {
            stateOut << state.dump(4);
            stateOut.close();
        }
        else {
            cout << "Error saving exam state." << endl;
        }
    }

    cout << "Exam completed! You scored " << score << " out of " << questionCount << "." << endl;

    // Resetting state file
    remove("exam_state.json");

    // Store the exam result
    ExamRecord record;
    record.studentID = loginId; 
    record.category = category;
    record.studentName = name; 
    record.score = score;

    // Load existing records
    FileManager fm;
    ifstream resultFile("exam_results.json");
    json results;

    if (resultFile.is_open()) {
        resultFile >> results;
        resultFile.close();
    }

    results.push_back(record.toJson());

    ofstream outFile("exam_results.json");
    if (outFile.is_open()) {
        outFile << results.dump(4);
        outFile.close();
    }
    else {
        cout << "Error: Unable to open file for writing..." << endl;
    }

    ExamMenu();
}

void StudentMenu::ViewCategories()
{
    ifstream file("tests.json");
    if (!file.is_open()) {
        cout << "Error opening tests.json!" << endl;
        return;
    }

    json tests;
    file >> tests;

    cout << "Number of Available Categories: " << tests.size() << endl;

    // Optionally, you can print the category names as well
    cout << "Available Categories:" << std::endl;
    for (const auto& item : tests) {
        cout << "- " << item["category"] << endl;
    }
    ExamMenu();
}

void StudentMenu::ViewExamResults()
{
    ifstream resultFile("exam_results.json");
    if (!resultFile.is_open()) {
        cout << "Error opening exam_results.json!" << endl;
        return;
    }

    json results;
    resultFile >> results;
    resultFile.close();

    bool recordsFound = false;
    int testCount = 0;

    cout << "Exam Records for Student ID: " << loginId << endl;

    for (const auto& record : results) {
        if (record["id"] == loginId) { // Match by student ID
            cout << "Category: " << record["category"] << ", Score: " << record["score"] << endl;
            recordsFound = true;
            testCount++;
        }
    }

    if (recordsFound) {
        cout << "Total Tests Taken: " << testCount << endl;
    }
    else {
        cout << "No exam records found for Student ID: " << loginId << endl;
    }

    ExamMenu();
}

void StudentMenu::Register()
{
    string fullName, address, phone, loginId, Password;
    cout << "Enter Full Name : "; cin >> fullName;
    cout << "Enter Address : "; cin >> address;
    cout << "Enter Phone Number : "; cin >> phone;
    cout << "Enter Your Login ID : "; cin >> loginId;
    cout << "Enter Your Password : "; cin >> Password;

    student.Register(loginId, Password, fullName, address, phone);
    DisplayMenu();
}

bool StudentMenu::Login()
{
    cout << "Enter Your ID : "; cin >> loginId;
    cout << "Enter Your Password : "; cin >> password;
    if (!student.Login(loginId, password)) {
        
        cout << "Login successfully. " << endl;
        ExamMenu();
        return true;
    }
    else {
        cout << "Login Unsuccessful" << endl;
        DisplayMenu();
        return false;
    }
}
