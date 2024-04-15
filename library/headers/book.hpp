#pragma once

#include <string>
#include <exception>
#include <initializer_list>
#include <iostream>

#include "isbn.hpp"
#include "author.hpp"
#include "title.hpp"

template <typename AuthorType, typename ISBNType, typename TitleType>
class Book {
private:
    Author<AuthorType> author;
    ISBN<ISBNType> isbn;
    Title<TitleType> title;
public:
	Book() = delete;
    Book(const AuthorType& a, const ISBNType& i, const TitleType& t)
        : author(a), isbn(i), title(t) {}

    void display() const {}
};