#include <sqlite3.h>
#include <sstream>
#include "Library.h"

int Book::add_book()
{
	cout<<"\nNEW BOOK ENTRY...\n";
	cout<<"Enter The Book Identity number:\n";//should this be generated
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



int main(void)
{
	Book b;
	b.add_book();
	return 0;
}

extern "C"
{
	Book* b_new()
	{
		return new Book();
	}

	void B_func(Book* book)
	{
		book -> add_book();
	}
}
