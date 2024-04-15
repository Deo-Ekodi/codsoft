#include <iostream>
#include <exception>

template <typename M, typename N, typename T>

T do_math(){
	std::cout << "Welcome to QuickMath" << std::endl;
	std::cout << "I will help you solve:"<<std::endl;
	std::cout << "addition" << std::endl;
	std::cout << "subtraction" << std::endl;
	std::cout << "multiplication" << std::endl;
	std::cout << "division" << std::endl << std::endl;

/**
  * get operands
  *
 */
	M x, N y;

	std::cout << "Enter two operands in that order" << std::endl;
	std::cin >> x >> y;

	if(!std::is_digit(x) || !std::is_digit(y)){
		throw std::invalid_argument("input values must be a digit!");
	}

	unsigned _seed{0};
	std::cout << "Enter operation as in:" << std::endl;
	std::cout << "[1] - addition [+]" << std::endl;
	std::cout << "[2] - subtraction [-]" << std::endl;
	std::cout << "[3] - multiplication [*]" << std::endl;
	std::cout << "[4] - division [/]" << std::endl;


	std::cin >> _seed;
	if(!(std::is_digit(_seed)) || (_seed < 1) || (_seed > 4)){
		throw std::invalid_argument("value must range from 1 - 4");
	}

	switch(_seed){
		case 1:
			return (sum(x, y));

		case 2:
			return (subtraction(x, y));

		case 3:
			return (multiplication(x, y));

		case 4:
			if(y == 0){
				throw std::invalid_argument("dividing by zero!");
			}
			return (division(x, y));
	}
	return -1;
}
