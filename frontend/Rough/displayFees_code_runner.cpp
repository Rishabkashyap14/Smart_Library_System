#include <iostream>
#include "Library.h"
#include <stdlib.h>

int main(int argc, const char* argv[]) {
	Return R;

	if (argc > 1) {
		R.userID= atoi(argv[1]);
		int x=R.Return_Fine();
	}

	//std::cout << "Book displayed successfully" << std::endl;
}
