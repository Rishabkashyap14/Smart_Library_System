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
	sqlite3_stmt *res;
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
	rc = sqlite3_prepare_v2(db, command.c_str(), -1, &res, 0);
    	if (rc == SQLITE_OK)
        	sqlite3_bind_int(res, 1, 3);
	else
        	fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    	int step = sqlite3_step(res);
	if (step == SQLITE_ROW) 
        	number_of_copies=sqlite3_column_int(res, 0);
	sqlite3_finalize(res);
	sqlite3_close(db);
	if(number_of_copies>0)
	{
		number_of_copies--;
		cout<<"Enter The Transaction Identity Number:"<<endl;
		cin>>transaction_id;
		cin.ignore();

		string status="Issued";

		time_t now = time(0);
		string issue_date = ctime(&now);

		cout<<"Enter The User Identity number:"<<endl;
		cin>>userID;
		cin.ignore();

		/* Open database */
		rc = sqlite3_open("book.db", &db);
		std::ostringstream sql1;
		if(rc) 
		{
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			return(0);
		} 
		else 
			fprintf(stderr, "Opened database successfully\n");
		sql1<<"INSERT INTO TRANSACTIONS VALUES ("<<transaction_id<<", '"<<status<<"', '"<<issue_date<<"', 0,"<<userID<<","<<book_id<<");UPDATE BOOKS SET Copies="<<number_of_copies<<" WHERE Book_Id="<<book_id;
		command=sql1.str();
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
