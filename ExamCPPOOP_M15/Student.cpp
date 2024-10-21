#include "Student.h"

void Student::Register(string RegisterID, string RegisterPassword, string fullname, string address, string phone)
{
	
	User* user = FindDiplicateName(fullname);
	if (user == nullptr) {
		users.push_back(User(RegisterID, RegisterPassword, fullname, address, phone));
		cout << "Register Successfully!" << endl;
		Save();
	}
	else {
		cout << "Account already Exist!" << endl;
	}
}
bool Student::Login(string LoginId, string LoginPassword)
{
	User* user = FindUserToLogin(LoginId, LoginPassword);
    RegisterID = user->RegisterID; // Set the ID
    fullName = user->fullName;      // Set the full name
	if (user == nullptr) {
		return true; 
	}
	return false; 
}
bool Student::DeleteStudent(string username)
{
	for (auto it = users.begin(); it != users.end(); it++) {
		if (it->fullName == username) {
			users.erase(it);
			Save(); 
			return true; 
		}
	}
	return false; 
}
void Student::UpdateUserID(string username, string newID)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.RegisterID = newID; 
			Save(); 
			return;
		}
	}
}

void Student::UpdateUserPassword(string username, string newPassword)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.RegisterPassword = newPassword;    
			Save(); 
			return;
		}
	}
}

void Student::UpdateUserFullName(string username, string newFullName)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.fullName = newFullName; 
			Save(); 
			return;
		}
	}
}

void Student::UpdateUserAddress(string username, string newAddress)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.address = newAddress; 
			Save(); 
			return;
		}
	}
}

void Student::UpdateUserPhone(string username, string newPhone)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.phone = newPhone; 
			Save(); 
			return;
		}
	}
}

void Student::TakeExam(string category)
{
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
    record.studentID = this->RegisterID;
    record.category = category;
    record.studentName = this->fullName;
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

}




void Student::ViewExamResults()
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

    cout << "Exam Records for Student ID: " << RegisterID << endl;

    for (const auto& record : results) {
        if (record["id"] == RegisterID) { // Match by student ID
            cout << "Category: " << record["category"] << ", Score: " << record["score"] << endl;
            recordsFound = true;
            testCount++;
        }
    }

    if (recordsFound) {
        cout << "Total Tests Taken: " << testCount << endl;
    }
    else {
        cout << "No exam records found for Student ID: " << RegisterID << endl;
    }
}



bool Student::UserExists(string username)
{
	for (const auto& user : users) {
		if (user.fullName == username) { 
			return true; // User exists
		}
	}
	return false; // User not found
}


void Student::Save()
{
	json contentJson = json::array();
	for (auto user : users) {
		contentJson.push_back(user.ConvertToJson());
	}
	filemanager.SaveUserInformationDataJson(contentJson);
}

void Student::Load()
{
	users.clear(); // for clear old user file 
    json contentJson = filemanager.LoadUserInformationDataJson();
    for (auto& j : contentJson) {
        User user;
        user.FromJson(j);
        users.push_back(user);
    }
} 


User* Student::FindDiplicateName(string fullname)
{
	for (auto& account : users) {
		if (account.fullName == fullname) {
			return &account;
		}
	}
	return nullptr;
}

User* Student::FindUserToLogin(string LoginId, string LoginPassword)
{
	for (auto& account : users) {
		if (account.RegisterID == LoginId && account.RegisterPassword == LoginPassword) {
			
			return &account;
		}
	}
	return nullptr;
}



