#include <iostream>
#include "Library.h"
#include <stdlib.h>

int main(int argc, const char* argv[]) {
	Return R;

	if (argc > 1) {
		R.user_id= atoi(argv[1]);
		R.book_name = argv[2];
		double x=R.Fine();
	}

	//std::cout << "Book displayed successfully" << std::endl;
}
