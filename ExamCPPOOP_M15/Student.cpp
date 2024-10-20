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
	if (user == nullptr) {
		// Retrieve full name
		return true; // Login successful
	}
	return false; // Login failed
}
bool Student::DeleteStudent(string username)
{
	for (auto it = users.begin(); it != users.end(); it++) {
		if (it->fullName == username) {
			users.erase(it);
			Save(); // Save changes after deletion
			return true; // Account deleted successfully
		}
	}
	return false; // User not found
}
void Student::UpdateUserID(string username, string newID)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.RegisterID = newID; // Update ID
			Save(); // Save changes
			return;
		}
	}
}

void Student::UpdateUserPassword(string username, string newPassword)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.RegisterPassword = newPassword; // Update password
			Save(); // Save changes
			return;
		}
	}
}

void Student::UpdateUserFullName(string username, string newFullName)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.fullName = newFullName; // Update full name
			Save(); // Save changes
			return;
		}
	}
}

void Student::UpdateUserAddress(string username, string newAddress)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.address = newAddress; // Update address
			Save(); // Save changes
			return;
		}
	}
}

void Student::UpdateUserPhone(string username, string newPhone)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.phone = newPhone; // Update phone
			Save(); // Save changes
			return;
		}
	}
}

bool Student::UserExists(string username)
{
	for (const auto& user : users) {
		if (user.fullName == username) { // Adjust this condition if you want to check by RegisterID
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



