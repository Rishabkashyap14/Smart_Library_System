#include <iostream>
#include "Library.h"
#include <stdlib.h>

int main(int argc, const char* argv[]) {
  Return R;

  if (argc > 1) {
    R.userID= atoi(argv[1]);
    R.book_name = argv[2];    
    int x = R.Return_Book();
  }

  std::cout << "Book returned successfully" << std::endl;
}

