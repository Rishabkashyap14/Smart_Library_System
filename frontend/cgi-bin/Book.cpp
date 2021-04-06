#include<iostream>
#include<iomanip>
#include<string>
#include<stdio.h>
#include<sqlite3.h>
#include<sstream>
#include<exception>
#include<stdlib.h>
#include  <bits/stdc++.h>
#include "Library.h"

using namespace std;

int Book::add_book()
{
/*	cout<<"\nNEW BOOK ENTRY...\n";
	cout<<"Enter The Book Identity number:\n";
	cin>>book_id;
	cin.ignore();
	cout<<"Enter The Name of The Book:\n";
	getline(cin,book_name);
	cout<<"Enter The Name of The Author:\n";
	getline(cin,author);
	cout<<"Enter The Number of Copies:\n";
	cin>>number_of_copies;
	cin.ignore();
	if(number_of_copies>0)
		availability=1;
	cout<<"Enter Description:\n";
	getline(cin,description);
*/
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	std::ostringstream sql;
	std::string command;
	/* Open database */
   	rc = sqlite3_open("/usr/lib/cgi-bin/book.db", &db);
   	if( rc ) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} 
	else 
		fprintf(stderr, "Opened database successfully\n");
	/* Create SQL statement */
	sql<<"INSERT INTO BOOKS VALUES (" <<book_id<< ", '" 
						 <<book_name<<"','"
						 <<author<<"','"
						 <<description<<"',"
						 <<number_of_copies<<")";
	command=sql.str();
	/* Execute SQL statement */
	rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} 
	else
		fprintf(stdout, "Records created successfully\n");
	sqlite3_close(db);
	return 0;//add other codes for error handling
}

int Book::remove_book()
{
	cout<<"\nDELETE A BOOK ENTRY...\n";
	cout<<"Enter The Book Identity number:\n";//should this be generated
	cin>>book_id;
	cin.ignore();
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	std::ostringstream sql;
	std::string command;
	/* Open database */
   	rc = sqlite3_open("book.db", &db);
   	if( rc ) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} 
	else 
		fprintf(stderr, "Opened database successfully\n");
	/* Create SQL statement */
	sql<<"DELETE FROM BOOKS WHERE Book_Id="<<book_id;
	command=sql.str();
	/* Execute SQL statement */
	rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} 
	sqlite3_close(db);
	return 0;
}

int Book::modify_book()
{
	cout<<"\nMODIFY BOOK INFORMATION...\n";
	cout<<"Enter The Book Identity number:\n";//should this be generated
	cin>>book_id;
	cin.ignore();
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	std::ostringstream sql;
	std::string command;
	/* Open database */
   	rc = sqlite3_open("book.db", &db);
   	if( rc ) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} 
	else 
		fprintf(stderr, "Opened database successfully\n");
	/* Create SQL statement */
	int choice;
	cout<<"Which Detail must be modified:\n";
	cout<<"1. Name of the Book 2. Author 3. Description 4. Number of Copies\n";
	cin>>choice;
	cin.ignore();
	switch(choice)
	{
		case 1:
			cout<<"Modified name:\n";
			getline(cin,book_name);
			sql<<"UPDATE BOOKS SET Book_name='"<<book_name<<"' WHERE Book_Id="<<book_id;
			break;
		case 2:
			cout<<"Modified name:\n";
			getline(cin,author);
			sql<<"UPDATE BOOKS SET Author='"<<author<<"' WHERE Book_Id="<<book_id;
			break;
		case 3:
			cout<<"Modified description:\n";
			getline(cin,description);
			sql<<"UPDATE BOOKS SET Description='"<<description<<"' WHERE Book_Id="<<book_id;
			break;
		case 4:
			cout<<"Modified number of copies:\n";
			cin>>number_of_copies;
			cin.ignore();
			sql<<"UPDATE BOOKS SET Copies="<<number_of_copies<<" WHERE Book_Id="<<book_id;
			break;	
		default:
			break;	
	}
	command=sql.str();
	/* Execute SQL statement */
	rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} 
	sqlite3_close(db);
	return 0;
}

int Book::print_info()
{
	cout<<"\nPRINT BOOK INFORMATION...\n";
	cout<<"Enter The Book Identity number:\n";//should this be generated
	cin>>book_id;
	cin.ignore();
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	std::ostringstream sql;
	std::string command;
	/* Open database */
   	rc = sqlite3_open("book.db", &db);
   	if( rc ) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} 
	else 
		fprintf(stderr, "Opened database successfully\n");
	/* Create SQL statement */
	sql<<"SELECT * FROM BOOKS WHERE Book_Id="<<book_id;
	command=sql.str();
	/* Execute SQL statement */
	rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} 
	sqlite3_close(db);
	return 0;
}


