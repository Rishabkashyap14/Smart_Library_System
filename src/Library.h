#include <iostream>

using namespace std;

int callback(void* data, int argc, char** argv, char** azColName);

class User
{
	protected:
    		int userID;
		int bookID;
    		std::string name;
    		std::string password;
    		std::string email;
    		std::string Utype;
    		char choice;
		int attempt;
	public:
		//Constructor
		User()
		{
			userID=0;
			bookID=0;
			name="Unknown";
			password="``````````";
			email="Unknown";
			Utype = "None";
			choice='$';
			attempt=0;
		};
		int create_user(string Utype);
		int show_user(void);
		int modify_user(void);
		int authenticate_user(void);//, std::string password);
};

class Book
{
	protected:
		//According to class diagram
		int book_id;
		std::string book_name;
		std::string author;
		int availability; //1 if available and 0 if not available

		//Some other extra variables
		std::string description;
		int number_of_copies;

	public:
		//Constructor
		Book()
		{
			book_id=0;
			book_name="Unknown";
			author="Unknown";
			availability=0;
			description="Unknown";
			number_of_copies=0;
		};

		//Methods, need to deal with database for these:
		int add_book();
		int remove_book();
		int modify_book();
		int print_info();
};

class Issue: public Book, public User
{
	private:
		std::string issue_date;
		std::string return_date;
		int transaction_id;
		Book b;
	public:
		Issue()
		{
			issue_date="";
			return_date="";
			transaction_id=0;
		};
		int User_Books();//Return Transaction id?
};

class Return: public Book, public User
{
	private:
		int transaction_id;
		std::string return_date;
		Book b;
	public:
		Return()
		{
			return_date="";
			transaction_id=0;
		};
		double Fine(int userID, int book_id);
		
		//Extra Function
		int Return_Book();//to update database
};

class Reserve: public Book, public User
{
	private:
		int book_id;
		int user_id;
		Book b;
	public:
		Reserve()
		{
			book_id=0;
			user_id=0;
		};
		int Reserve_Book();
};

class Student : public Issue, public Return 
{
	public:
		Student()
		{
			Issue::Utype="Student";
		}
		void issue_book()
		{
			int issue= Issue::User_Books();
		};
		void return_book()
		{
			int Return= Return::Return_Book();
		};
		void reserve_book()
		{
		};
};

class Administrator : public Return
{
	public:
		void Register_user()
		{
			cout<<"Enter The type of User:\n";
			getline(cin,Utype);
			int new_user=Return::create_user(Utype);
		};
		void Calculate_fine()
		{
			cout<<"Enter the userID: \n";
			cin>>userID;
			cin.ignore();
			cout<<"Enter the bookID: \n";
			cin>>book_id;
			cin.ignore();
			cout<<Return::Fine(userID, book_id);
		};
};

class Librarian : public Issue, public Return
{
	public:
		void Add_new()
		{
			int b=Issue::add_book();
		};
		void Remove_book()
		{
			int r=Issue::remove_book();
		};
		void Update_book()
		{
			int modify=Issue::modify_book();
		};
		void Issue_book()
		{
			int issue= Issue::User_Books();
		};
		void Return_book()
		{
			int Return= Return::Return_Book();
		};
};
