#pragma once
#include <iostream>
#include <vector>
#include "book.h"

class user
{
	struct User_S
	{
		std::string username;
		std::string password;
		int permision;
		Book BookData;

		User_S() : username(""), password(""), permision(0){}

		User_S(std::string UserName, std::string UserPassword, int permision, Book UsersBooks)
			: username(UserName), password(UserPassword), permision(permision), BookData(UsersBooks){}
	};

private:
	User_S LoggedAccount;

	void GetAllUsers();
	void LoadUsersFromFile();
	void SaveUsersToFile();
public:
	std::vector<User_S> Users;
	Book BooksData;

	user() {
		LoadUsersFromFile();
		BooksData.InitializeDefaultBooks();
	}

	void login();
	void doOperation();
	void RegisterUser();
	void AddBookToUser(const std::string& bookName, const std::string& bookWriter);
	void BorrowBook();
};

