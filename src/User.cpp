#include<iostream>
#include<iomanip>
#include<string.h>
#include<exception>

using namespace std;

class User
{
	private:
    		int userID;
		int book_ID;
    		char name[20];
    		char password[10];
    		char choice;
		int attempt;
	public:
		void create_user(void)
		{
		    	cout<<"\nNEW USER ENTRY...\n";
		    	cout<<"\nEnter The User Identity number:"<<endl;
		    	cin>>userID;
		    	cout<<"\n\nEnter The Name of The User:"<<endl;
		    	fgets(name);
		    	cout<<"\n\nNew User Record Created!";
		}

		void show_user(void)
		{
			cout<<"Enter the user ID:"<<endl;
			cin>>userID;
			//Search SQL databasefor the same
		    	cout<<"\nUser Identity number: "<<userID;
		    	cout<<"\nUser Name :"<<name<<endl;
		}

		void modify_user(void)
		{
			cout<<"Enter the user ID:"<<endl;
			cin>>userID;
			//Search SQL databasefor the same
		    	cout<<"\nUser Identification Number: "<<UserID;
		    	cout<<"\nModify User Name :"<<endl;
			cin>>name;
		    	cout<<"Do you wish to change password? Y/N"<<endl;
		    	cin>>choice;
			switch(choice)
			{
				case 'Y':
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
					break;
			}
		    	
		}

		int authenticate_user(int userID, char* password)
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
					cin.ignore(numeric_limits<streamsize>::max, '\n');
					cout<<"You have entered an invalid input, try again:"<<endl;
					cin>>userID;
					attempt++;
				}
				if(!cin.fail && attempt<3)
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
		};
		void return_book()
		{
		};
		void reserve_book()
		{
		};
}
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
class Administrator : public User
{
	public:
		void Register_user();
		void Add_book_details();
		void Calculate_fine();
}
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
class Librarian : public User
{
	public:
		void Add_new();
		void Remove_book();
		void Update_book();
		void Issue_book();
}
