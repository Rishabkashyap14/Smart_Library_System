#include <iostream>
#include "Library.h"
#include <stdlib.h>

int main(int argc, const char* argv[])
{
	User u;
	if (argc > 1)
	{
		u.userID = atoi(argv[1]);
		u.name = argv[2];
		u.password = argv[3];
		u.email = argv[4];
		
		int x = b.create_user();
	}
	std::cout << "User added successfully" << std::endl;
	return 0;
}

