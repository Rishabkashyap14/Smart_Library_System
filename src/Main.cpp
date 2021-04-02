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
	z=b.print_info();*/

	//Testing for User Class
	/*User u;
	int a=u.create_user();
	int b=u.show_user();
	int c=u.modify_user();*/

	//Testing for Issue class
	/*Issue i;
	Return r;
	int m=i.User_Books();
	cout<<r.Fine();
	int k = r.Return_Book();*/

	//Testing for Student Class
	Student s;
	s.issue_book();
	s.return_book();
	return 0;
}
