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

void Admin::CreateAccount(string RegisterID, string RegisterPassword, string fullname, string address, string phone)
{
    student.Register(RegisterID, RegisterPassword, fullname, address, phone); 
}

void Admin::DeleteAccount(string userName)
{
    if (student.DeleteStudent(userName)) {
        if (DeleteExamRecords(userName)) {
            cout << "Account and exam records deleted successfully!" << endl;
        }
        else {
            cout << "Account deleted, but failed to delete exam records." << endl;
        }
    }
    else {
        cout << "Error: Account deletion failed. User may not exist." << endl;
    }
}

bool Admin::DeleteExamRecords(string username)
{
    ifstream resultFile("exam_results.json");
    if (!resultFile.is_open()) {
        cout << "Error opening exam_results.json!" << endl;
        return false;
    }

    json results;
    resultFile >> results;
    resultFile.close();

    json updatedResults;
    bool recordsDeleted = false;

    for (const auto& record : results) {
        if (record["id"] != username) { 
            updatedResults.push_back(record);
        }
        else {
            recordsDeleted = true; // Found and deleted record for the user
        }
    }

    // Save updated results back to the file
    ofstream outFile("exam_results.json");
    if (outFile.is_open()) {
        outFile << updatedResults.dump(4);
        outFile.close();
        return recordsDeleted; 
    }
    else {
        cout << "Error: Unable to open file for writing..." << endl;
        return false;
    }
}

void Admin::ChangeUserInformation(string userName)
{
    if (!student.UserExists(userName)) {
        cout << "Error: User does not exist." << endl;
        return;
    }

    int choice;
    string oldName = student.fullName;
    string oldId = student.RegisterID;
    cout << "============ CHANGE USER INFORMATION ============" << endl;
    cout << "1) Change ID" << endl;
    cout << "2) Change Password" << endl;
    cout << "3) Change Full Name" << endl;
    cout << "4) Change Address" << endl;
    cout << "5) Change Phone" << endl;
    cout << "6) Back" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        string newID;
        cout << "Enter new Register ID: ";
        cin >> newID;
        student.UpdateUserID(userName, newID);
        cout << "Calling UpdateExamRecords with oldID: " << userName << ", newID: " << newID << ", oldName: " << oldName << ", newName: " << oldName << endl;
        UpdateExamRecords(userName, newID, oldName, oldName);
        cout << "User ID updated successfully!" << endl;
        break;
    }
    case 2: {
        string newPassword;
        cout << "Enter new password: ";
        cin >> newPassword;
        student.UpdateUserPassword(userName, newPassword); 
        cout << "Password updated successfully!" << endl;
        break;
    }
    case 3: {
        string newFullName;
        cout << "Enter new full name: ";
        cin.ignore();
        getline(cin, newFullName);
        student.UpdateUserFullName(userName, newFullName); 
        UpdateExamRecords(oldId, oldId, oldName, newFullName); 
        cout << "Full name updated successfully!" << endl;
        break;
    }
    case 4: {
        string newAddress;
        cout << "Enter new address: ";
        cin.ignore();
        getline(cin, newAddress);
        student.UpdateUserAddress(userName, newAddress); 
        cout << "Address updated successfully!" << endl;
        break;
    }
    case 5: {
        string newPhone;
        cout << "Enter new phone number: ";
        cin.ignore();
        getline(cin, newPhone);
        student.UpdateUserPhone(userName, newPhone); 
        cout << "Phone number updated successfully!" << endl;
        break;
    }
    case 6:
        return;
    default:
        cout << "Invalid option. Please try again." << endl;
        ChangeUserInformation(userName);
        break;
    }
}
void Admin::UpdateExamRecords(string oldID, string newID, string oldName, string newName)
{
    ifstream resultFile("exam_results.json");
    if (!resultFile.is_open()) {
        cout << "Error opening exam_results.json!" << endl;
        return;
    }

    json results;
    resultFile >> results;
    resultFile.close();

    bool updated = false;

    for (auto& record : results) {
        cout << "Checking record with ID: " << record["id"] << " and Name: " << record["name"] << endl;
        if (record["id"] == oldID) {
            cout << "Updating ID from " << oldID << " to " << newID << endl;
            record["id"] = newID; 
            updated = true;
        }
        if (record["name"] == oldName) {
            cout << "Updating name from " << oldName << " to " << newName << endl;
            record["name"] = newName; 
            updated = true;
        }
    }

    if (updated) {
        ofstream outFile("exam_results.json");
        if (outFile.is_open()) {
            outFile << results.dump(4); 
            outFile.close();
            cout << "Exam records updated successfully!" << endl;
        }
        else {
            cout << "Error: Unable to open file for writing..." << endl;
        }
    }
    else {
        cout << "No records updated." << endl;
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
    tests.erase(tests.begin() + testIndex); 
    fm.saveTests(tests, fileName); 
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
    tests[testIndex].questions.erase(tests[testIndex].questions.begin() + questionIndex); 
    fm.saveTests(tests, fileName); 
    cout << "Question deleted successfully!" << endl;
}

void Admin::displayCategories()
{
    cout << "Available Categories:" << endl;
    for (int i = 0; i < tests.size(); ++i) {
        cout << i + 1 << ": " << tests[i].category << endl;
    }
}

void Admin::addExamRecord(string studentId, string category, string name, int score)
{
    ExamRecord newRecord(studentId, category, name, score); 
    vector<ExamRecord> records;
    fm.LoadExamRecord(records); 
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

