#pragma once
#include <iostream>
#include "json.hpp"
#include <fstream>
using json = nlohmann::json;
using namespace std;
class User
{
public:
	string RegisterID, RegisterPassword;
	string fullName, address, phone;

	User() = default;
	User(string RegisterID, string RegisterPassword, string fullname, string address, string phone);


	
	void Display();

	json ConvertToJson();
	void FromJson(json j);
};
