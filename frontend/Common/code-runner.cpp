#include <iostream>
#include "Library.h"
#include <stdlib.h>

int main(int argc, const char* argv[]) {
  Book b;

  if (argc > 1) {
    b.book_id = atoi(argv[1]);
    b.book_name= argv[2];
    b.author = argv[3];
    b.description = argv[4];
    b.number_of_copies = atoi(argv[5]);
    int x=b.add_book();
  }

  std::cout << "Book inserted successfully" << std::endl;
}

