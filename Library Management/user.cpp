#include "user.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
void user::LoadUsersFromFile() {
	std::ifstream infile("users.txt");
	std::string line;
	User_S currentUser;

	while (std::getline(infile, line)) {
		if (line.rfind("USER,", 0) == 0) { // Check if the line starts with "USER,"
			std::istringstream ss(line.substr(5)); // Skip "USER,"
			std::string username, password;
			int permission;

			std::getline(ss, username, ','); // Read until the first comma
			std::getline(ss, password, ','); // Read until the second comma
			ss >> permission; // Read permission

			// Create a new user
			currentUser = User_S(username, password, permission, Book());
		}
		else if (line.rfind("BOOK,", 0) == 0) { // Check if the line starts with "BOOK,"
			std::istringstream ss(line.substr(5)); // Skip "BOOK,"
			std::string bookName, bookWriter;
			bool userHasOnAccount;

			std::getline(ss, bookName, ','); // Read until the first comma
			std::getline(ss, bookWriter, ','); // Read until the second comma
			ss >> userHasOnAccount; // Read userHasOnAccount

			// Add the book to the current user's BookData
			currentUser.BookData.Books.push_back(Book::BookProperty_S(bookName, bookWriter, userHasOnAccount));
		}
		else if (line == "ENDUSER") {
			// Add the current user to the Users vector when we hit "ENDUSER"
			Users.push_back(currentUser);
		}
	}
	infile.close(); // Close the file after reading
}


void user::SaveUsersToFile()
{
	std::ofstream outfile("users.txt");
	for (const auto& user : Users) {
		// Save user data
		outfile << "USER," << user.username << "," << user.password << "," << user.permision << "\n";

		// Save the user's books
		for (const auto& book : user.BookData.Books) {
			outfile << "BOOK," << book.Name << "," << book.Writer << "," << book.UserHasOnAccount << "\n";
		}
		outfile << "ENDUSER\n"; // Mark the end of the user data
	}
	outfile.close(); // Close the file after writing
}

void user::GetAllUsers()
{
	int index = 0;
	for (const auto& user : Users) {
		if (user.permision != 2)
		{
			string Perm;
			if (user.permision == 0)
			{
				Perm = "User";
			}
			else {
				Perm = "Admin";
			}
			index++;
			cout << index << " | Name: " << user.username << " | Perm: " << Perm << " |" << endl;
		}
	}
}

void user::login()
{
	system("cls");
	if (LoggedAccount.username == "")
	{
		string username;
		string password;
		bool userFound = false;

		cout << "Please enter your account name: ";
		cin >> username;
		for (const auto& user : Users)
		{
			if (username == user.username)
			{
				cout << "Please enter your password: ";
				cin >> password;

				if (user.password == password)
				{
					LoggedAccount = user;
					system("cls");
					GetAllUsers();
					doOperation();
					return;
				}
				else
				{
					cout << "Username or password is incorrect\n";
				}
				userFound = true;
				break;
			}
		}

		if (!userFound) {
			cout << "Wrong username\n";
		}
	}
	else
	{
		doOperation();
	}

}

void user::doOperation()
{
	int selection;
	char op = 0;
	if (LoggedAccount.permision == 1)
	{
		cout << "1. Register User\n2. Display all users\n3. Add Book to User\n4. Log Out\n";
		cin >> selection;

		switch (selection)
		{
		case 1:
			system("cls");
			RegisterUser();
			login();
			break;
		case 2:
			system("cls");
			GetAllUsers();
			cout << "Do you want to go back (y/n): ";
			cin >> op;
			if (op == 'y' || op == 'Y')
			{
				login();
				break;
			}
			else {
				break;
			}
		case 3:
		{
			std::string bookName, bookWriter;
			std::cout << "Enter book name: ";
			std::cin.ignore();
			std::getline(std::cin, bookName);
			std::cout << "Enter book writer: ";
			std::getline(std::cin, bookWriter);
			AddBookToUser(bookName, bookWriter);
			break;
		}
		case 4:
			LoggedAccount = User_S("", "", 0, Book());
			login();
			break;
		default:
			cout << "Enter valid operation id\n";
			break;
		}
	}
	else
	{
		system("cls");
		cout << "1. Borrow a book\n2. Log Out\n3. My Books\n";
		cin >> selection;
		char op;

		switch (selection)
		{
		case 1:
			BorrowBook();
			login();
			break;
		case 2:
			LoggedAccount = User_S("", "", 0, Book());
			login();
			break;
		case 3:
			LoggedAccount.BookData.ListAvailableBooks();
			cout << "Do you want to go back (y/n): ";
			cin >> op;
			if (op == 'y' || op == 'Y')
			{
				login();
				break;
			}
			else {
				break;
			}
		default:
			cout << "Enter valid operation id\n";
			break;
		}
	}
}

void user::RegisterUser()
{
	string name, password;
	bool isRegistered = false;

	cout << "Create the account name: ";
	cin >> name;

	for (const auto& user : Users) {
		if (name == user.username)
		{
			cout << "This account is allready registered\n";
			isRegistered = true;
			break;
		}
	}

	if (!isRegistered) {
		cout << "Create the password for the account: ";
		cin >> password;

		Users.emplace_back(name, password, 0, Book());
		cout << "Account successfuly registered!\n";
		SaveUsersToFile();
	}
}

void user::BorrowBook()
{
	if (LoggedAccount.permision == 0)
	{
		for (const auto& books : Book().Books)
		{
			cout << books.Name << endl;
		}
		string bookName;

		cout << "Enter the name of the book you want to borrow: ";
		cin.ignore();
		getline(cin, bookName);

		bool borrowed = LoggedAccount.BookData.BorrowBookForUser(bookName);
		if (borrowed)
		{
			cout << "Book borrowed successfully!\n";
		}
		else
		{
			cout << "Could not borrow the book.\n";
		}
	}
	else
	{
		cout << "Admins cannot borrow books.\n";
	}
}

void user::AddBookToUser(const std::string& bookName, const std::string& bookWriter)
{
	// Check if the book already exists in the user's collection
	for (const auto& book : LoggedAccount.BookData.Books) {
		if (book.Name == bookName && book.Writer == bookWriter) {
			std::cout << "This book is already added to your account.\n";
			return;  // Exit if the book already exists
		}
	}

	// If the book does not exist, add it
	LoggedAccount.BookData.Books.emplace_back(bookName, bookWriter, false);
	SaveUsersToFile(); // Save after adding a book
}



