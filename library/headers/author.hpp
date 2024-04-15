#pragma once

#include <iostream>
#include <string>

template <typename T>
class Author {
private:
    T name;
public:
	Author() = default;
    Author(T n) : name(n) {}
    T getName() const { return name; }
	void setName(const T& n){
		name = n;
	}
};