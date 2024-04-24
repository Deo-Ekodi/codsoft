#pragma once

#include <string>


template <typename T>
class ISBN {
private:
    T number;
public:
	ISBN() = default;
    ISBN(T num) : number(num) {}
	T get_isbn()const{
		return number;
	}
	void set_isbn(T num){
		number = num;
	}
};