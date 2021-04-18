#include <iostream>
#include "Library.h"
#include <stdlib.h>

int main(int argc, const char* argv[]) {
  Issue I;

  if (argc > 1) {
    I.book_name = argv[1];
    I.userID= atoi(argv[2]);
    int x = I.User_Books();
  }

  std::cout << "Book issued successfully" << std::endl;
}

