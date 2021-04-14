#include <iostream>
#include "Library.h"
#include <stdlib.h>

int main(int argc, const char* argv[]) {
  Return R;

  if (argc > 1) {
    R.book_name = argv[1];
    R.userID= atoi(argv[2]);
    int x = R.User_Books();
  }

  std::cout << "Book issued successfully" << std::endl;
}

