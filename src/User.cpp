#include<iostream>
#include<iomanip>
#include<string.h>
#include<exception>
#include<stdlib.h>
#include<sstream>
#include<ios>
#include<sqlite3.h>
#include<stdio.h>
#include<limits>
#include"Library.h"

using namespace std;

int User::authenticate_user(int userID, string password)
{
	attempt = 0;
	cout<<"Enter the userID:"<<endl;
	cin>>userID;
	//Error Handling
	while(1)
	{
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout<<"You have entered an invalid input, try again:"<<endl;
			cin>>userID;
			attempt++;
		}
		if(!cin.fail() && attempt<3)
			break;
		if(attempt>1)
		{
			cout<<"Three incorrect tries, cannot proceed"<<endl;
			exit(0);
		}
	}
	//Successful UserID entered
	//Try-Catch for wrong password, (Need more test cases)
	try{
		cout<<"Enter the password"<<endl;
		cin>>password;
	}
	catch(bad_alloc& e){
		cout<<e.what()<<"Invalid password size"<<endl;
	}
}

int User::create_user(void)
{
	cout<<"\nNEW USER ENTRY...\n";
	cout<<"Enter The User Identity number:"<<endl;
	cin>>userID;
	cin.ignore();
	cout<<"Enter The Name of The User:\n";
	getline(cin,name);
	//cin.ignore();
	cout<<"Enter The New Password:\n";
	cin>>password;
	cin.ignore();
	cout<<"Enter your email address:\n";
	cin>>email;
	cin.ignore();
	cout<<"Enter The type of User:\n";
	cin>>Utype;
	cin.ignore();
	//authenticate_user(userID, password);
		    	
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
	sql<<"INSERT INTO USERS VALUES ("<<userID<<", '"<<name<<"', '"<<password<<"', '"<<email<<"', '"<<Utype<<"')";
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
		return 0;
		cout<<"\n\nNew User Record Created!";
	}

int User::show_user(void)
{
	cout<<"\nPRINT USER INFORMATION...\n";
	cout<<"Enter The User Identity number:\n";//should this be generated
	cin>>userID;
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
	sql<<"SELECT User_id,User_name,Email,UserType FROM USERS WHERE User_id="<<userID;
	command=sql.str();
	/* Execute SQL statement */
	rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} 
	return 0;
}

int User::modify_user(void)
{
	cout<<"Enter the user ID:"<<endl;
	cin>>userID;
	cout<<"What do you wish to change?\n1 - User name\n2 - Password\n3- Email\n4 - User Type\n5 - All Good, exit"<<endl;
	cin>>choice;
	int flag = 0;
	while(!flag)
	{
		switch(choice)
		{
			case '1':
			{
				cout<<"Enter the new user name:\n";
				getline(cin,name);
				cin.ignore();
				sqlite3 *db;
				char *zErrMsg = 0;
				int rc;
				std::ostringstream sql;
				std::string command;
				rc = sqlite3_open("book.db", &db);
				if( rc ) 
				{
					fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
					return(0);
				} 
				else 
					fprintf(stderr, "Opened database successfully\n");
				sql<<"UPDATE USERS SET User_name = '"<<name<<"' WHERE User_id = "<<userID;
				command=sql.str();
				rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
				if( rc != SQLITE_OK )
				{
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				}
				break;
			}
			case '2':
			{
				cout<<"Enter the user name:\n";
				getline(cin,name);
				cin.ignore();
				cout<<"Enter the previous password:"<<endl;
				cin>>password;
				cin.ignore();
				sqlite3 *db;
				char *zErrMsg = 0;
				int rc;
				std::ostringstream sql;
				std::string command;
				rc = sqlite3_open("book.db", &db);
				if( rc ) 
				{
					fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
					return(0);
				} 
				else 
					fprintf(stderr, "Opened database successfully\n");
				sql<<"SELECT Password FROM USERS WHERE UserName = '"<<name<<"' AND UserID = "<<userID<<"AND Password = '"<<password<<"'";
				command=sql.str();
				rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
				if( rc != SQLITE_OK )
				{
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				}
				if(rc!=SQLITE_NULL)
				{
					cout<<"Enter the new password"<<endl;
					cin>>password;
					cin.ignore();
					sql<<"UPDATE USERS SET Password = '"<<password<<"' WHERE UserID = "<<userID<<";";
					command=sql.str();
					rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
					if( rc != SQLITE_OK )
					{
						fprintf(stderr, "SQL error: %s\n", zErrMsg);
						sqlite3_free(zErrMsg);
					}
				}
				break;
			}

			default:
				cout<<"Incorrect option, please try again"<<endl;
				break;
		}
	//}		    	
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/
class Student : public User
{
	private:
		int userID;
		int book_ID;
		char name[20];
		char password[10];
		char choice;
	public:
		void issue_book(int userID, int bookID)
		{
			printf("Enter user password:\n");
			//authenticate_user(userID, password);
			
			sqlite3 *db;
			char *zErrMsg = 0;
			int rc;
			std::ostringstream sql;
			std::string command;
			rc = sqlite3_open("book.db", &db);
			if( rc ) 
			{
				fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
				return(0);
			} 
			else 
				fprintf(stderr, "Opened database successfully\n");
			sql<<"DELETE FROM BOOKS WHERE BookID = '"<<bookID;
			command=sql.str();
			rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
			if( rc != SQLITE_OK )
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			sqlite3_close(db);
		};
		void return_book(int userID, int bookID)
		{
			printf("Enter user password:\n");
			//authenticate_user(userID, password);
			
			cout<<"Enter the Book Name: \n:";
			getline(cin, 
			transaction_id++;
			sqlite3 *db;
			char *zErrMsg = 0;
			int rc;
			std::ostringstream sql;
			std::string command;
			rc = sqlite3_open("book.db", &db);
			if( rc ) 
			{
				fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
				return(0);
			} 
			else 
				fprintf(stderr, "Opened database successfully\n");
			//Adding the new book into the BOOKS table
			sql<<"SELECT Copies FROM BOOKS WHERE Book_id = '"<<bookID<<"';";
			command=sql.str();
			rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
			if( rc != SQLITE_OK )
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			int copies = atoi(getline(cout, int));
			copies++;
			sql<<"UPDATE BOOKS SET Copies = "<<copies<<" WHERE Book_id = "bookID<<";";
			command=sql.str();
			rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   it
			if( rc != SQLITE_OK )
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			sql<<"INSERT INTO TRANSACTIONS VALUES ("<<transaction_id<<", "<<book_name<<", Return, "<<;
			command=sql.str();
			rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
			if( rc != SQLITE_OK )
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			sqlite3_close(db);
		};
		void reserve_book()
		{
		};
};
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
class Administrator : public User
{
	public:
		void Register_user();
		void Add_book_details();
		void Calculate_fine();
};
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
class Librarian : public User
{
	public:
		void Add_new();
		void Remove_book();
		void Update_book();
		void Issue_book();
};
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
