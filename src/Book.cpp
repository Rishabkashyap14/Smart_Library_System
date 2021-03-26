#include<iostream>
#include<iomanip>
#include<string>
#include<stdio.h>
#include<sqlite3.h>
#include<sstream>
#include<exception>
#include<stdlib.h>
#include  <bits/stdc++.h>

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    return 0;
}

class Book
{
	private:
		//According to class diagram
		int book_id;
		string book_name;
		string author;
		int availability; //1 if available and 0 if not available

		//Some other extra variables
		string description;
		int number_of_copies;

	public:
		//Constructor
		Book()
		{
			book_id=0;
			book_name="Unknown";
			author="Unknown";
			availability=0;
			description="Unknown";
			number_of_copies=0;
		};

		//Methods, need to deal with database for these:
		int add_book();
		int remove_book();
		int modify_book();
		int print_info();
};

int Book::add_book()
{
	cout<<"\nNEW BOOK ENTRY...\n";
	cout<<"\nEnter The Book Identity number:"<<endl;//should this be generated
	cin>>book_id;
	cout<<"\n\nEnter The Name of The Book:"<<endl;
	getline(cin,book_name);
	cout<<"\nEnter The Name of The Author:"<<endl;
	getline(cin,author);
	cout<<"\nEnter The Number of Copies:"<<endl;
	cin>>number_of_copies;
	if(number_of_copies>0)
		availability=1;
	cout<<"\n\nEnter Description:"<<endl;
	getline(cin,description);
	sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   std::ostringstream sql;
   std::string command;

   /* Open database */
   rc = sqlite3_open("book.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql<<"INSERT INTO BOOKS VALUES (" <<book_id<< ", '" 
						 <<book_name<<"','"
						 <<author<<"','"
						 <<description<<"',"
						 <<number_of_copies<<")";
   command=sql.str();
   /* Execute SQL statement */
   rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);
	return 0;//add other codes for error handling
}
/*int Book::remove_book()
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
class Issue: public Book, public User
{
	private:
		char *issue_date;
		char *return_date;
		int transaction_id;
	public:
		Issue()
		{
			issue_date="";
			return_date="";
			transaction_id=0;
		};
		int User_Books();//Return Transaction id?
}
int Issue::User_Books()
{
	return 0;
}
class Return: public Book, public User
{
	private:
		int transaction_id;
		char *return_date;
	public:
		Return()
		{
			return_date="";
			transaction_id=0;
		};
		int Fine();
		
		//Extra Function
		int Return_Book();//to update database
}
int Return::Fine()
{
	int number_of_days=0;
	//Write Code to get number of days
	return number_of_days*2;
}
int Return::Return_Book()
{
	return 0;
}
class Reserve: public Book, public User
{
	private:
		int book_id;
		int user_id;
	public:
		Reserve()
		{
			book_id=0;
			user_id=0;
		};
		int Reserve_Book();
}
int Reserve::Reserve_Book()
{
	return 0;
}*/
int main()
{
	Book b;
	int x=b.add_book();
	return 0;
}
