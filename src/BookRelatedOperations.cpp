#include "Library.h"
#include <ctime>
#include <sqlite3.h>
#include <stdio.h>
#include <sstream>

using namespace std;

int Issue::User_Books()
{
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
	if(rc) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} 
	else 
		fprintf(stderr, "Opened database successfully\n");
	sql<<"SELECT Copies FROM BOOKS WHERE Book_id="<<book_id;
	command=sql.str();
	rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} 
	else
		fprintf(stdout, "Records created successfully\n");
	cout<<rc;
	sqlite3_close(db);
	if(availability==1)
	{
		number_of_copies--;
		cout<<"Enter The Transaction Identity Number:"<<endl;
		cin>>transaction_id;
		cin.ignore();

		string status="Issued";

		time_t issue_date = time(0);
		string dt = ctime(&issue_date);

		cout<<"Enter Return Date:\n";
		getline(cin,return_date);

		cout<<"Enter The User Identity number:"<<endl;
		cin>>userID;
		cin.ignore();

		/* Open database */
		rc = sqlite3_open("book.db", &db);
		if(rc) 
		{
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			return(0);
		} 
		else 
			fprintf(stderr, "Opened database successfully\n");
		sql<<"INSERT INTO TRANSACTIONS VALUES ("<<transaction_id<<", '"<<status<<"', '"<<issue_date<<"', '"<<return_date<<"',"<<userID<<book_id<<")";
		command=sql.str();
		rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
		if( rc != SQLITE_OK )
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} 
		else
			fprintf(stdout, "Records created successfully\n");
		sqlite3_close(db);
		if(number_of_copies==0)
			availability=0;
	}
	return 0;
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

int Reserve::Reserve_Book()
{
	return 0;
}
