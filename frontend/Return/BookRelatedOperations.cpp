#include "Library.h"
#include <ctime>
#include <time.h>
#include <sqlite3.h>
#include <stdio.h>
#include <sstream>

using namespace std;

int Issue::User_Books()
{
//	cout<<"Enter The Book Name number:\n";
//	getline(cin, book_name);
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
	sql<<"SELECT Copies FROM BOOKS WHERE Book_name='"<<book_name<<"';";
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
//		cout<<"Enter The Transaction Identity Number:"<<endl;
//		cin>>transaction_id;
//		cin.ignore();

		string status="Issued";

		time_t now = time(0);
		string issue_date = ctime(&now);

//		cout<<"Enter The User Identity number:"<<endl;
//		cin>>userID;
//		cin.ignore();

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
		
		std::ostringstream sql2; 
		sql2<<"SELECT Book_id FROM BOOKS WHERE Book_name='"<<book_name<<"';";
		command=sql2.str();
		rc = sqlite3_prepare_v2(db, command.c_str(), -1, &res, 0);
    	if (rc == SQLITE_OK)
        	sqlite3_bind_int(res, 1, 3);
		else
        	fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    	int step = sqlite3_step(res);
		if (step == SQLITE_ROW) 
        	book_id=sqlite3_column_int(res, 0);
		
		srand(time(0));
		int transaction_id = rand();
		sql1<<"INSERT INTO TRANSACTIONS VALUES ("<<transaction_id<<", '"<<status<<"', '"<<issue_date<<"', 0,"<<userID<<","<<book_id<<");UPDATE BOOKS SET Copies="<<number_of_copies<<" WHERE Book_name='"<<book_name<<"';";
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

double Return::Fine(int userID, string book_name)
{
	double number_of_days=0; 
	time_t now = time(0); 
	string return_date = ctime(&now); 
	struct tm tm;
	const char* issue_date; 
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
	
	std::ostringstream sql4; 
	sql4<<"SELECT Book_id FROM BOOKS WHERE Book_name='"<<book_name<<"';";
	command=sql4.str();
	rc = sqlite3_prepare_v2(db, command.c_str(), -1, &res, 0);
	if (rc == SQLITE_OK)
    	sqlite3_bind_int(res, 1, 3);
	else
    	fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
	int step1 = sqlite3_step(res);
	if (step1 == SQLITE_ROW) 
    	book_id=sqlite3_column_int(res, 0);
    	
	sql<<"SELECT Date FROM TRANSACTIONS where User_id = "<<userID<<" AND Book_id="<<book_id<<";";
	command=sql.str();
	rc = sqlite3_prepare_v2(db, command.c_str(), -1, &res, 0);
    	if(rc == SQLITE_OK)
        	sqlite3_bind_int(res, 1, 3);
	else
        	fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    	int step = sqlite3_step(res);
	if (step == SQLITE_ROW) 
        	issue_date=reinterpret_cast<const char*>(sqlite3_column_text(res, 0));
	sqlite3_finalize(res);
	sqlite3_close(db);
	strptime(issue_date, "%a %b %d %H:%M:%S %Y", &tm);// Converts a string of time into a tm structural entity
	//tm.tm_year = tm.tm_year - 1900;
	//tm.tm_year = tm.tm_year + 2021;
	//tm.tm_hour = tm.tm_hour - 1;
	time_t t = mktime(&tm);// Convert string into time
	number_of_days=difftime(now,t); // Finds the difference in the two input times
	cout<<return_date;
	cout<< asctime(&tm);
	return number_of_days/(60 * 60 * 24) ;
}
int Return::Return_Book()
{
//	cout<<"Enter the userID: \n";
//	cin>>userID;
//	cin.ignore();
//	cout<<"Enter the bookID: \n";
//	cin>>book_id;
//	cin.ignore();
	double x = Fine(userID, book_name);
	sqlite3 *db;
	sqlite3_stmt *res;
	char *zErrMsg = 0;
	int rc;
	std::ostringstream sql1;
	std::string command;
	if(x>=7)
	{
		x = 10 + (x-7)*2;
		cout<<x;
		/* Open database */
		rc = sqlite3_open("book.db", &db);
		if(rc) 
		{
			fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
			return(0);
		} 
		else 
			fprintf(stderr, "Opened database successfully\n");
		sql1<<"UPDATE USERS set Fees ="<<x<<" WHERE User_id="<<userID<<";";
		command=sql1.str();
		rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
		if( rc != SQLITE_OK )
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		sqlite3_close(db);
	}
	/* Open database */
	rc = sqlite3_open("book.db", &db);
	
	std::ostringstream sql4; 
	sql4<<"SELECT Book_id FROM BOOKS WHERE Book_name='"<<book_name<<"';";
	command=sql4.str();
	rc = sqlite3_prepare_v2(db, command.c_str(), -1, &res, 0);
	if (rc == SQLITE_OK)
    	sqlite3_bind_int(res, 1, 3);
	else
    	fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
	int step = sqlite3_step(res);
	if (step == SQLITE_ROW) 
    	book_id=sqlite3_column_int(res, 0);
    sqlite3_close(db);	
    	
	rc = sqlite3_open("book.db", &db);
	std::ostringstream sql2;
	if(rc) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} 
	else 
		fprintf(stderr, "Opened database successfully\n");
	sql2<<"UPDATE TRANSACTIONS set Status='Returned' WHERE User_id="<<userID<<" AND Book_id="<<book_id<<"; UPDATE BOOKS SET Copies=Copies+1 WHERE Book_name='"<<book_name<<"';";
	command=sql2.str();
	rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	sqlite3_close(db);
	return 0;
}

int Reserve::Reserve_Book()
{
	return 0;
}
