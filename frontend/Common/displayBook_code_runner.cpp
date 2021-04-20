#include <iostream>
#include "Library.h"
#include <stdlib.h>

int main(int argc, const char* argv[]) {
	Book b;

	if (argc > 1) {
		b.book_id= atoi(argv[1]);
		int x=b.print_info();
	}

	//std::cout << "Book displayed successfully" << std::endl;
}
