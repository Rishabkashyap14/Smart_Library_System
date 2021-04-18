#include <iostream>
#include "Library.h"
#include <stdlib.h>

int main(int argc, const char* argv[]) {
	Book b;

	if (argc > 1) {
		b.book_id= atoi(argv[1]);
		b.book_name=argv[2];
		int x=b.remove_book();
	}

	std::cout << "Book removed successfully" << std::endl;
}

