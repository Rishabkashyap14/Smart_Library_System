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

int User::authenticate_user(int userID)//, string password)
{
	cout<<"Enter the password for user: "<<userID<<"\n";
	cin>>password;
	cin.ignore();
	int attempt = 0;
	const char* pwd;
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
	sql<<"SELECT Password FROM USERS where User_id = "<<userID<<";";
	command=sql.str();
	rc = sqlite3_prepare_v2(db, command.c_str(), -1, &res, 0);
    	if(rc == SQLITE_OK)
        	sqlite3_bind_text(res, 1, 3);
	else
        	fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    	int step = sqlite3_step(res);
	if (step == SQLITE_ROW) 
        	pwd=reinterpret_cast<const char*>(sqlite3_column_text(res, 0));
	sqlite3_finalize(res);
	sqlite3_close(db);
	attempt++;
	int compare = password.compare(pwd);
	while(attempt <= 3)
	{
		if(compare != 0)	
		{
			cout<<"Password is incorrect\n";
			attempt++;
		}
		else
			cout<<"Successful Authentication!\n\n";
	}
	return 1;
	/*while(1)
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
	}*/
	//Successful UserID entered
	//Try-Catch for wrong password, (Need more test cases)
	/*try{
		cout<<"Enter the password"<<endl;
		cin>>password;
	}
	catch(bad_alloc& e){
		cout<<e.what()<<"Invalid password size"<<endl;
	}*/
	/*sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	std::ostringstream sql;
	std::string command;
	rc=sqlite3_open("book.db",&db);
	if(rc) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return(0);
	} 
	else 
		fprintf(stderr, "Opened database successfully\n");
	sql<< "SELECT name from USERS WHERE User_id="<<userID<<" AND password='"<<password<<"'";
	command=sql.str();*/
	/* Execute SQL statement */
	//rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);
	//cout<<rc;
	
}

int User::create_user(string Utype)
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
	//cout<<"Enter The type of User:\n";
	//cin>>Utype;
	//cin.ignore();
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
		cout<<"\n\nNew User Record Created!";
		return 1;
	}

int User::show_user(void)
{
	cout<<"\nPRINT USER INFORMATION...\n";
	cout<<"Enter The User Identity number:\n";//should this be generated
	cin>>userID;
	cin.ignore();
	authenticate_user(UserID, password);
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
	sqlite3_close(db);
	return 0;
}

int User::modify_user(void)
{
	cout<<"Enter the user ID:"<<endl;
	cin>>userID;
	cout<<"What do you wish to change?\n1 - User name\n2 - Password\n3- Email\n4 - User Type\n5 - All Good, exit"<<endl;
	cin>>choice;
	cin.ignore();
	int flag=0;
	switch(choice)
	{
		case '1':
		{
			cout<<"Enter the new user name:\n";
			getline(cin,name);
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
			sqlite3_close(db);
			break;
		}
		case '2':
		{
			cout<<"Enter the user name:\n";
			getline(cin,name);
			cout<<"Enter the previous password:"<<endl;
			getline(cin,password);
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
			sql<<"SELECT Password FROM USERS WHERE User_name = '"<<name<<"' AND User_id = "<<userID<<" AND Password = '"<<password<<"';";
			command=sql.str();
			rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
			if( rc != SQLITE_OK )
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			if(rc!=SQLITE_NULL)
			{
				cout<<"Enter the new password\n";
				getline(cin,password);
				cout<<password;
				sql<<"UPDATE USERS SET Password = '"<<password<<"' WHERE User_id = "<<userID;
				command=sql.str();
				rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
				if( rc != SQLITE_OK )
				{
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				}
			}
			sqlite3_close(db);
			break;
		}
		case '3':
		{
			cout<<"Enter the new user email id:\n";
			getline(cin,email);
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
			sql<<"UPDATE USERS SET Email = '"<<email<<"' WHERE User_id = "<<userID;
			command=sql.str();
			rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
			if( rc != SQLITE_OK )
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			sqlite3_close(db);
			break;
		}
		case '4':
		{
			cout<<"Enter the new user type:\n";
			getline(cin,Utype);
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
			sql<<"UPDATE USERS SET UserType = '"<<Utype<<"' WHERE User_id = "<<userID;
			command=sql.str();
			rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
			if( rc != SQLITE_OK )
			{
				fprintf(stderr, "SQL error: %s\n", zErrMsg);
				sqlite3_free(zErrMsg);
			}
			sqlite3_close(db);
			break;
		}
		default:
			cout<<"Incorrect option, please try again"<<endl;
			break;
	}	    	
}

/*-------------------------------------------------------------------------------------------------------------------------------------------*/
class Student : public User, public Book
{
	protected:
		int userID;
		int book_ID;
		char name[20];
		char password[10];
		char choice;
	public:
		void issue_book(int userID, int bookID)
		{
			//How are we supposed to make a different thing for this?
		};
		void return_book()
		{
			printf("Enter user password:\n");
			authenticate_user(userID, password);
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
};*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*class Administrator : public User, public Return, public Book
{
	public:
		void Register_user();
		void Calculate_fine();
};

void Administrator::Register_User(void)
{
	Utype = 'Administrator';
	if(!create_user(Utype))
	{
		cout<<"Error creating User\n";
		return 0;
	}
	return 1;
}

void Add_book_details(int book_id)
{
	cout<<"Enter the user ID:\n";
	cin>>userID;
	
}

*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/*class Librarian : public User
{
	public:
		void Add_new();
		void Remove_book();
		void Update_book();
		void Issue_book();
};*/
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
