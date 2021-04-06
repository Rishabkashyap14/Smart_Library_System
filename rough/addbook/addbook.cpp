#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h>
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
	
	form_iterator fi = formData.getElement("Book_id");  
	if( !fi->isEmpty() && fi != (*formData).end()) 
	{  
		cout << "Book name:" << **fi << endl;
		b.book_id = **fi;  
	} 
	else 
	{
		cout << "No text entered for Book Id, don't lose hope" << endl;  
	}
	cout << "<br/>\n";
	cout << "</body>\n";
	cout << "</html>\n";

	return 0;
}
   
   
