#pragma once

#include "book.hpp"

template <class T = Book>
class Database
{
	private:
	// linked list implementation
		T* head;
		T* tail;
	public:
		Database();
		void run();
		bool add();
		bool remove(const T&);
		bool search(const T&);
		bool checkout(const T&);
		bool return_book(const T&);
		bool fine();
};

Database::Database(){
	head = tail = nullptr;
}

void Database::add(){
	AUTHOR* author = new AUTHOR;
	TITLE* title = new TITLE;
	ISBN* isbn = new ISBN;
    BOOK* book = new BOOK;

    std::string str;
    std::cout << "Enter Author: " << std::flush;
    std::cin >> str;
    author->set_author(&str);

    std::cout << "Enter title: " << std::flush;
    std::cin >> str;
    title->set_title(&str);

    std::cout << "Enter isbn: " << std::flush;
    std::cin >> str;
    isbn->set_isbn(&str);

    book->author = author;
    book->title = title;
    book->isbn = isbn;

	if(head == nullptr){
		head = book;
		book->next = tail;
	}
}