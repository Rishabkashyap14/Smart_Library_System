#include<iostream>
#include<iomanip>
#include<string.h>
#include<exception>

using namespace std;

class Book
{
	private:
		//According to class diagram
		int book_id;
		char *book_name;
		char *author;
		int availability; //1 if available and 0 if not available

		//Some other extra variables
		char *description;
		int number_of_copies;

	public:
		//Constructor
		Book()
		{
			book_id=0;
			book_name="";
			author="";
			availability=0;
			description="";
			number_of_copies=0;
		};

		//Methods, need to deal with database for these:
		int add_book();
		int remove_book();
		int modify_book();
		int print_info();
}

int Book::add_book()
{
	cout<<"\nNEW BOOK ENTRY...\n";
	cout<<"\nEnter The Book Identity number:"<<endl;//should this be generated
	cin>>book_id;
	cout<<"\n\nEnter The Name of The Book:"<<endl;
	fgets(book_name);
	cout<<"\n\nEnter The Name of The Author:"<<endl;
	fgets(author);
	cout<<"\n\nEnter The Number of Copies:"<<endl;
	cin>>number_of_copies;
	if(number_of_copies>0):
		availability=1;
	cout<<"\n\nEnter Description:"<<endl;
	fgets(description);
	/* Add code to insert into database */
	cout<<"\n\nNew Book Record Created!";
	return 0;//add other codes for error handling
}

int Book::remove_book()
{
	return 0;
}

int Book::modify_book()
{
	return 0;
}

int print_info()
{
	return 0;
}
