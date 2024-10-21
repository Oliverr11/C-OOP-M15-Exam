#include "AdminMenu.h"

void AdminMenu::MainMenu()
{
    cout << "============ WELCOME ============" << endl;
	cout << "1 ) Modify User " << endl; // can create account ,delete account, change information and password
    cout << "2 ) View Statistics" << endl;
    cout << "3 ) Manage Test" << endl;
    int opt;
    cout << "Enter Option : "; cin >> opt;
    switch (opt)
    {
    case 1 :
        ModifyUserMenu();
        break;
    case 3 :
        ManageTestMenu();
        break;
    default:
        break;
    }
}

void AdminMenu::ModifyUserMenu()
{
    cout << "============ MODIFY USER ============" << endl;
    cout << "1 ) Create Account" << endl;
    cout << "2 ) Delete Account" << endl;
    cout << "3 ) Change Information" << endl;
    cout << "4 ) Back" << endl;
    int opt;
    cout << "Enter Option : "; cin >> opt;
    switch (opt)
    {
    case 1: 
        CreateAccount();
        break;
    case 2 : 
        DeleteAccount();
        break;
    case 3 : 
        ChangeUserInformation();
        break;
    default:
        MainMenu();
        break;
    }

}

void AdminMenu::ManageTestMenu()
{
    cout << "============ WELCOME ============" << endl;
    cout << "1 ) Add Category" << endl;
    cout << "2 ) Add Questions to category" << endl;
    cout << "3 ) Delete Category" << endl;
    cout << "4 ) Delete Questions from category" << endl;
    cout << "5 ) Display Category" << endl;
    cout << "6 ) Back" << endl;
    int opt;
    cout << "Enter Option : "; cin >> opt;
    switch (opt)
    {
    case 1 : 
        AddCategory();
        break;
    case 2 :
        AddQuestionCategory();
        break;
    case 3 : 
        DeleteCategory();
        break;
    case 4 : 
        DeleteQuestionFromCategory();
        break;
    case 5 : 
        displayCategories();
    default:
        MainMenu();
        break;
    }
}

void AdminMenu::CreateAccount()
{
    string RegisterID, RegisterPassword, fullname, address, phone;

    cout << "Enter Register ID: ";
    cin >> RegisterID;
    cout << "Enter Register Password: ";
    cin >> RegisterPassword;
    cout << "Enter Full Name: ";
    cin.ignore(); 
    getline(cin, fullname);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Phone: ";
    getline(cin, phone);
    admin.CreateAccount(RegisterID, RegisterPassword, fullname, address, phone); 
    ModifyUserMenu();
}

void AdminMenu::DeleteAccount()
{
    string username;

    cout << "Enter username to delete: ";
    cin >> username;
    admin.DeleteAccount(username);
    MainMenu();
}


void AdminMenu::ChangeUserInformation()
{
    string username;
    cout << "Enter username to modify: ";
    cin >> username;
    admin.ChangeUserInformation(username);
    MainMenu();
}

void AdminMenu::AddCategory()
{
    string category;
    cout << "Enter Category name : "; cin >> category;
    admin.addCategory(category);
    ManageTestMenu();
}

void AdminMenu::AddQuestionCategory()
{
    cout << "Available Categories:" << endl;
    for (int i = 0; i < admin.tests.size(); ++i) {
        cout << i << ": " << admin.tests[i].category << endl; 
    }

    int testIndex;
    cout << "Enter the test index to add a question (0 for first test): ";
    cin >> testIndex;

    if (testIndex < 0 || testIndex >= admin.tests.size()) {
        cerr << "Error: Invalid test index." << endl;
        ManageTestMenu();
        return;
    }

    string questionText;
    vector<string> options;
    string option;
    int correctAnswer;

    cout << "Enter question text: ";
    cin.ignore(); 
    getline(cin, questionText);

    cout << "Enter the number of options: ";
    int numOptions;
    cin >> numOptions;

    if (numOptions < 2) {
        cerr << "Error: At least two options are required." << endl;
        ManageTestMenu(); 
        return;
    }

    cout << "Enter the options:" << endl;
    for (int i = 0; i < numOptions; ++i) {
        cout << "Option " << i + 1 << ": ";
        cin >> option;
        options.push_back(option);
    }

    cout << "Enter the index of the correct answer (starting from 0): ";
    cin >> correctAnswer;

    if (correctAnswer < 0 || correctAnswer >= numOptions) {
        cerr << "Error: Correct answer index is out of range." << endl;
        ManageTestMenu(); 
        return;
    }

    try {
        admin.addQuestionToCategory(testIndex, questionText, options, correctAnswer);
        cout << "Question added successfully!" << endl;
    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    ManageTestMenu(); 
}

void AdminMenu::DeleteCategory()
{
    cout << "Available Categories:" << endl;
    for (size_t i = 0; i < admin.tests.size(); ++i) {
        cout << i << ": " << admin.tests[i].category << endl; 
    }

    int testIndex;
    cout << "Enter the test index to delete (0 for first test): ";
    cin >> testIndex;

    if (testIndex < 0 || testIndex >= admin.tests.size()) {
        cerr << "Error: Invalid test index." << endl;
        ManageTestMenu(); 
        return;
    }

    try {
        admin.deleteCategory(testIndex);
    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    ManageTestMenu(); 
}

void AdminMenu::DeleteQuestionFromCategory()
{
    cout << "Available Categories:" << endl;
    for (int i = 0; i < admin.tests.size(); i++) {
        cout << i << ": " << admin.tests[i].category << endl; 
    }

    int testIndex;
    cout << "Enter the test index to delete a question from (0 for first test): ";
    cin >> testIndex;

    if (testIndex < 0 || testIndex >= admin.tests.size()) {
        cerr << "Error: Invalid test index." << endl;
        ManageTestMenu(); 
        return;
    }

    cout << "Questions in category \"" << admin.tests[testIndex].category << "\":" << endl;
    for (int i = 0; i < admin.tests[testIndex].questions.size(); ++i) {
        cout << i << ": " << admin.tests[testIndex].questions[i].questionText << endl; 
    }

    int questionIndex;
    cout << "Enter the question index to delete (0 for first question): ";
    cin >> questionIndex;

    if (questionIndex < 0 || questionIndex >= admin.tests[testIndex].questions.size()) {
        cerr << "Error: Invalid question index." << endl;
        ManageTestMenu();
        return;
    }

    try {
        admin.deleteQuestionFromCategory(testIndex, questionIndex);
    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    ManageTestMenu(); 
}

void AdminMenu::displayCategories()
{
    admin.displayCategories();
    ManageTestMenu();
}


void AdminMenu::Login()
{
    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
        
    if (admin.Login(username, password)) {
        cout << "Login successful!" << std::endl;
        MainMenu();
    }
    else {
        cout << "Login failed. Invalid username or password." << std::endl;
    }
}