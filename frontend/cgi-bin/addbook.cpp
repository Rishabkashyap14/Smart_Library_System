#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h>
#include<sqlite3.h>
#include<sstream>
#include<exception>
#include "Library.h"

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h> 

using namespace std;
using namespace cgicc;

int main(void)
{
	Cgicc formData;
	Book b;
   
	cout << "Content-type:text/html\r\n\r\n";
	cout << "<html>\n";
	cout << "<head>\n";
	cout << "<title>Adding a new book</title>\n";
	cout << "</head>\n";
	cout << "<body>\n";
	
	form_iterator fi_1 = formData.getElement("Book_id");  
	if( !fi_1->isEmpty() && fi_1 != (*formData).end()) 
	{  
		cout << "Book ID:" << **fi_1 << endl;
		b.book_id = stoi(**fi_1);  
	} 
	else 
	{
		cout << "No text entered for Book Id" << endl;  
	}

	cout<< "<br>";
	
	form_iterator fi_2 = formData.getElement("Book_name");  
	if( !fi_2->isEmpty() && fi_2 != (*formData).end()) 
	{  
		cout << "Book name:" << **fi_2 << endl;
		b.book_name = **fi_2;  
	} 
	else 
	{
		cout << "No text entered for Book Name" << endl;  
	}

	cout<< "<br>";
	
	form_iterator fi_3 = formData.getElement("Author");  
	if( !fi_3->isEmpty() && fi_3 != (*formData).end()) 
	{  
		cout << "Author:" << **fi_3 << endl;
		b.author = **fi_3;  
	} 
	else 
	{
		cout << "No text entered for Author" << endl;  
	}
	
	cout<< "<br>";

	form_iterator fi_4 = formData.getElement("Copies");  
	if( !fi_4->isEmpty() && fi_4 != (*formData).end()) 
	{  
		cout << "Number Of Copies:" << **fi_4 << endl;
		b.number_of_copies = stoi(**fi_4);  
	} 
	else 
	{
		cout << "No text entered for Number of Copies" << endl;  
	}
	
	cout<< "<br>";

	form_iterator fi_5 = formData.getElement("Book_Description");  
	if( !fi_5->isEmpty() && fi_5 != (*formData).end()) 
	{  
		cout << "Description:" << **fi_5 << endl;
		b.description = **fi_5;  
	} 
	else 
	{
		cout << "No text entered for Description" << endl;  
	}

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
	sql<<"INSERT INTO BOOKS VALUES (" <<b.book_id<< ", '" 
						 <<b.book_name<<"','"
						 <<b.author<<"','"
						 <<b.description<<"',"
						 <<b.number_of_copies<<")";
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

	cout<< "<br>";

	cout << "<br/>\n";
	cout << "</body>\n";
	cout << "</html>\n";

	return 0;
}
   
   
