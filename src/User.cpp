#include<iostream>
#include<iomanip>
#include<string.h>

using namespace std;

class User
{
	private:
    		int userID;
		int book_ID;
    		char name[20];
    		char password[6];
    		char choice;
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
		void issue_book(int userID, int book_ID)
		{
			
}

