#pragma once
#include <iostream>
#include <vector>

class Book
{
public:
	struct BookProperty_S
	{
		std::string Name;
		std::string Writer;
		bool UserHasOnAccount;

		BookProperty_S() : Name(""), Writer(""), UserHasOnAccount(false) {}

		BookProperty_S(std::string BooksName, std::string BooksWriter, bool UserHasOnTheAccount)
			: Name(BooksName), Writer(BooksWriter), UserHasOnAccount(UserHasOnTheAccount){}
	};
public:
	std::vector<BookProperty_S> Books;

    Book() {
        Books.push_back(BookProperty_S("Kürk Mantolu Madonna", "Sabahattin Ali", false));
        Books.push_back(BookProperty_S("1984", "George Orwell", false));
    }

    void InitializeDefaultBooks() {
        if (Books.empty()) {
            Books.push_back(BookProperty_S("Kürk Mantolu Madonna", "Sabahattin Ali", false));
            Books.push_back(BookProperty_S("1984", "George Orwell", false));
        }
    }

    bool BorrowBookForUser(const std::string& bookName)
    {
        for (auto& book : Books)
        {
            if (book.Name == bookName && !book.UserHasOnAccount)
            {
                book.UserHasOnAccount = true;
                std::cout << "You have successfully borrowed the book: " << bookName << std::endl;
                return true;
            }
        }
        std::cout << "The book is either not available or already borrowed.\n";
        return false;
    }

    void ListAvailableBooks()
    {
        std::cout << "| Available Books:\n";
        for (const auto& book : Books)
        {
            if (book.UserHasOnAccount)
            {
                std::cout << "Book: " << book.Name << " by " << book.Writer << " |" << std::endl;
            }
        }
    }
};

