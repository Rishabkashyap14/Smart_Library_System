#include "Library.h"
#include <iostream>

using namespace std;

int main()
{
	//Testing for book class
	/*Book book;
	int x=b.add_book();
	int y=b.remove_book();
	x=b.add_book();
	int z=book.print_info();
	x=b.add_book();
	z=b.print_info();
	int w=b.modify_book();
	z=b.print_info();
	y=b.remove_book();
	z=b.print_info();

	
	User u;
	int a=u.create_user();
	int b=u.show_user();
	int c=u.modify_user();*/

	//Testing for Issue class
	Issue i;
	Return r;
	int m=i.User_Books();
	cout<<r.Fine();
	return 0;
}
