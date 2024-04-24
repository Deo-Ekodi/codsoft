#pragma once

#include <string>
#include <concepts>

#include "isbn.hpp"
#include "author.hpp"
#include "title.hpp"

template <typename AuthorType = std::string, typename ISBNType = std::string, typename TitleType = std::string>

class Book {
private:
    Author<AuthorType> author;
    ISBN<ISBNType> isbn;
    Title<TitleType> title;
    bool checked_out;
    time_t checkout_date;
public:
	Book() = default;
    Book(
        const AuthorType& a, 
        const ISBNType& i, 
        const TitleType& t
        ):
        author(a), 
        isbn(i), 
        title(t), 
        checked_out(false), 
        checkout_date(std::time(nullptr)){}

    bool is_checked_out()const {
        return checked_out;
    }

    void return_book(){
        checked_out = false;
        checkout_date = std::time(nullptr);
    }

    time_t get_checkout_date() const{
        return checkout_date;
    }

    std::ostringstream display() const {
        std::ostringstream os;
        os << this->author.getName() << " " << this->isbn->get_isbn() << " " << this->title->getTitle() << std::flush;
        return os;
    }
};