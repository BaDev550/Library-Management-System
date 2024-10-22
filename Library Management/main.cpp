#include <iostream>
#include <Windows.h>
#include "user.h"

int main() {
	user UserData;
	bool ApplicationShoudClose = false;
	char op;

	while (!ApplicationShoudClose)
	{
		UserData.login();

		Sleep(500);
		std::cout << "Do you wanna close the app? (y/n): ";
		std::cin >> op;
		
		if (op == 'y' || op == 'Y')
		{
			ApplicationShoudClose = true;
			break;
		}
		else
		{
			system("cls");
		}
	}
	return 0;
}