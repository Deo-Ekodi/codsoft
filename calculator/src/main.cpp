/** Simple Calculator
  * c++ implementation
 */

#include <iostream>

int main(){
	try{
		do_math();
	}
	catch(std::invalid_argument& v){
		std::cerr << v.what() << std::flush;
	}

	return 0;
}
