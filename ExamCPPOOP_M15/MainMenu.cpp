#include "MainMenu.h"

void MainMenu::Menu()
{
	cout << "============ WELCOME TO IT STEP-ACADEMY ============" << endl;
	cout << " 1 ) Admin " << endl;
	cout << " 2 ) Student " << endl;
	int opt;
	cout << "Enter Option : "; cin >> opt;
	switch (opt)
	{
	case 1  :
		adminMenu();
		break;
	case 2 : 
		studentMenu();
		break;
	default:
		break;
	}
}

void MainMenu::studentMenu()
{
	StudentMenu sm;
	sm.DisplayMenu();
}

void MainMenu::adminMenu()
{
	AdminMenu am;
	am.Login();
}

