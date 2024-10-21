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
    student.TakeExam(category);

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
    student.ViewExamResults();
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
