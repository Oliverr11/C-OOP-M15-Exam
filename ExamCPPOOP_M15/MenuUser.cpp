#include "MenuUser.h"


void MenuUser::DisplayMenu()
{

	
	cout << "============= WELCOME =============" << endl;
	cout << "1. Register " << endl;
	cout << "2. Login " << endl;
	int opt;
	cout << "Enter Option : "; cin >> opt;
	switch (opt)
	{
	case 1 : 
		Register();
		break;
	case 2 : 
		Login();
		break;
	default:
		break;
	}

}

void MenuUser::Register()
{
	string fullName, address, phone, loginId, Password;
	cout << "Enter Full Name : "; cin >> fullName;
	cout << "Enter Address : "; cin >> address;
	cout << "Enter Phone Number : "; cin >> phone;
	cout << "Enter Your Login ID : "; cin >> loginId;
	cout << "Enter Your Password : "; cin >> Password;
	
	user.Register(loginId, Password, fullName, address, phone);
	DisplayMenu();
}

void MenuUser::Login()
{
	
	string loginId, password;
	cout << "Enter Your ID : "; cin >> loginId;
	cout << "Enter Your Password : "; cin >> password;
	user.Login(loginId, password);
	if (!user.Login(loginId, password)) {
		cout << "Login Succesfully." << endl;
	}
	else {
		cout << "Login Unsuccesfully" << endl;
	}
	DisplayMenu(); 
}

