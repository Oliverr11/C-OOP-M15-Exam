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
    cin.ignore(); // Clear the newline character from the input buffer
    getline(cin, fullname);
    cout << "Enter Address: ";
    getline(cin, address);
    cout << "Enter Phone: ";
    getline(cin, phone);

    student.Register(RegisterID, RegisterPassword, fullname, address, phone); // Call the Register function
    ModifyUserMenu(); // Return to the menu after registration
}

void AdminMenu::DeleteAccount()
{
    string username;

    cout << "Enter username to delete: ";
    cin >> username;

    // Assuming the Student class has a method to delete a user
    if (student.DeleteStudent(username)) {
        cout << "Account deleted successfully!" << endl;
    }
    else {
        cout << "Error: Account deletion failed. User may not exist." << endl;
    }

    ModifyUserMenu(); // Return to the menu
}

void AdminMenu::ChangeUserInformation()
{
    string username;
    cout << "Enter username to modify: ";
    cin >> username;

    // Check if the user exists
    if (!student.UserExists(username)) {
        cout << "Error: User does not exist." << endl;
        ModifyUserMenu(); // Return to the menu
        return;
    }

    int choice;
    cout << "============ CHANGE USER INFORMATION ============" << endl;
    cout << "1) Change ID" << endl;
    cout << "2) Change Password" << endl;
    cout << "3) Change Full Name" << endl;
    cout << "4) Change Address" << endl;
    cout << "5) Change Phone" << endl;
    cout << "6) Back to Modify User Menu" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        string newID;
        cout << "Enter new Register ID: ";
        cin >> newID;
        student.UpdateUserID(username, newID); // Method to update user ID
        cout << "User ID updated successfully!" << endl;
        break;
    }
    case 2: {
        string newPassword;
        cout << "Enter new password: ";
        cin >> newPassword;
        student.UpdateUserPassword(username, newPassword); // Method to update user password
        cout << "Password updated successfully!" << endl;
        break;
    }
    case 3: {
        string newFullName;
        cout << "Enter new full name: ";
        cin.ignore();
        getline(cin, newFullName);
        student.UpdateUserFullName(username, newFullName); // Method to update full name
        cout << "Full name updated successfully!" << endl;
        break;
    }
    case 4: {
        string newAddress;
        cout << "Enter new address: ";
        cin.ignore();
        getline(cin, newAddress);
        student.UpdateUserAddress(username, newAddress); // Method to update address
        cout << "Address updated successfully!" << endl;
        break;
    }
    case 5: {
        string newPhone;
        cout << "Enter new phone number: ";
        cin.ignore();
        getline(cin, newPhone);
        student.UpdateUserPhone(username, newPhone); // Method to update phone
        cout << "Phone number updated successfully!" << endl;
        break;
    }
    case 6:
        // Go back to the modify user menu
        ModifyUserMenu();
        return;
    default:
        cout << "Invalid option. Please try again." << endl;
        ChangeUserInformation();
        break;
    }
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
    // Display available categories
    cout << "Available Categories:" << endl;
    for (size_t i = 0; i < admin.tests.size(); ++i) {
        cout << i << ": " << admin.tests[i].category << endl; // Show category index and name
    }

    int testIndex;
    cout << "Enter the test index to add a question (0 for first test): ";
    cin >> testIndex;

    // Validate test index
    if (testIndex < 0 || testIndex >= admin.tests.size()) {
        cerr << "Error: Invalid test index." << endl;
        ManageTestMenu(); // Return to the menu
        return;
    }

    string questionText;
    vector<string> options;
    string option;
    int correctAnswer;

    cout << "Enter question text: ";
    cin.ignore(); // Ignore the newline character from previous input
    getline(cin, questionText);

    cout << "Enter the number of options: ";
    int numOptions;
    cin >> numOptions;

    // Validate number of options
    if (numOptions < 2) {
        cerr << "Error: At least two options are required." << endl;
        ManageTestMenu(); // Return to the menu
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

    // Validate correct answer index
    if (correctAnswer < 0 || correctAnswer >= numOptions) {
        cerr << "Error: Correct answer index is out of range." << endl;
        ManageTestMenu(); // Return to the menu
        return;
    }

    try {
        admin.addQuestionToCategory(testIndex, questionText, options, correctAnswer);
        cout << "Question added successfully!" << endl;
    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    ManageTestMenu(); // Return to the menu
}

void AdminMenu::DeleteCategory()
{
    // Display available categories
    cout << "Available Categories:" << endl;
    for (size_t i = 0; i < admin.tests.size(); ++i) {
        cout << i << ": " << admin.tests[i].category << endl; // Show category index and name
    }

    int testIndex;
    cout << "Enter the test index to delete (0 for first test): ";
    cin >> testIndex;

    // Validate test index
    if (testIndex < 0 || testIndex >= admin.tests.size()) {
        cerr << "Error: Invalid test index." << endl;
        ManageTestMenu(); // Return to the menu
        return;
    }

    try {
        admin.deleteCategory(testIndex);
    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    ManageTestMenu(); // Return to the menu
}

void AdminMenu::DeleteQuestionFromCategory()
{
    // Display available categories
    cout << "Available Categories:" << endl;
    for (size_t i = 0; i < admin.tests.size(); ++i) {
        cout << i << ": " << admin.tests[i].category << endl; // Show category index and name
    }

    int testIndex;
    cout << "Enter the test index to delete a question from (0 for first test): ";
    cin >> testIndex;

    // Validate test index
    if (testIndex < 0 || testIndex >= admin.tests.size()) {
        cerr << "Error: Invalid test index." << endl;
        ManageTestMenu(); // Return to the menu
        return;
    }

    // Display available questions for the selected category
    cout << "Questions in category \"" << admin.tests[testIndex].category << "\":" << endl;
    for (size_t i = 0; i < admin.tests[testIndex].questions.size(); ++i) {
        cout << i << ": " << admin.tests[testIndex].questions[i].questionText << endl; // Show question index and text
    }

    int questionIndex;
    cout << "Enter the question index to delete (0 for first question): ";
    cin >> questionIndex;

    // Validate question index
    if (questionIndex < 0 || questionIndex >= admin.tests[testIndex].questions.size()) {
        cerr << "Error: Invalid question index." << endl;
        ManageTestMenu(); // Return to the menu
        return;
    }

    try {
        admin.deleteQuestionFromCategory(testIndex, questionIndex);
    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }

    ManageTestMenu(); // Return to the menu
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