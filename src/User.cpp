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
	cout<<"\nEnter The User Identity number:"<<endl;
	cin>>userID;
	cin.ignore();
	cout<<"\n\nEnter The Name of The User:"<<endl;
	getline(cin,name);
	cin.ignore();
	cout<<"\n\nEnter The Name of The User:\n";
	cin>>name;
	cin.ignore();
	cout<<"\n\nEnter The new password:\n";
	cin>>password;
	cin.ignore();
	cout<<"Enter your email address:\n";
	cin>>email;
	cin.ignore();
	cout<<"\n\nEnter The type of User:\n";
	cin>>Utype;
	cin.ignore();
	authenticate_user(userID, password);
		    	
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
	sql<<"INSERT INTO USER VALUES ("<<userID<<", '"<<name<<"', '"<<password<<"', '"<<email<<"', '"<<Utype<<"');";
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

void User::show_user(void)
{
	cout<<"Enter the user ID:"<<endl;
	cin>>userID;
	//Search SQL databasefor the same
	cout<<"\nUser Identity number: "<<userID;
	cout<<"\nUser Name :"<<name<<endl;
}

int User::modify_user(void)
{
	cout<<"Enter the user ID:"<<endl;
	cin>>userID;
	cout<<"What do you wish to change?\n1 - User name\n2 - Password\n3- Email\n4 - User Type\n5 - All Good, exit"<<endl;
	cin>>choice;
	while(1)
	{
		switch(choice)
		{
			case '1':
				cout<<"Enter the new user name:\n";
				cin>>name;
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
				sql<<"UPDATE USER SET UserName = '"<<name<<"' WHERE UserID = "<<userID<<";";
				command=sql.str();
				rc = sqlite3_exec(db, command.c_str(), callback, 0, &zErrMsg);   
				if( rc != SQLITE_OK )
				{
					fprintf(stderr, "SQL error: %s\n", zErrMsg);
					sqlite3_free(zErrMsg);
				}
				break;
			/*case 'Y':
				cout<<"Enter the previous password:"<<endl;
				//Compare with SQL query if the password matches
				//If it matches do the below, else break
				cout<<"Enter the new password"<<endl;
				cin>>password;
				break;
			case 'N':
				break;
			default:
				cout<<"Incorrect option, please try again"<<endl;
				break;*/
		}
	}		    	
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
			//Check SQL query for password
			//SQL query to remove book and add it to transaction table
		};
		void return_book()
		{
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
