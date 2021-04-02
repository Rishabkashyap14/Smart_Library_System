#include <iostream>

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
		int create_user(void);
		int show_user(void);
		int modify_user(void);
		int authenticate_user(int userID, std::string password);
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
	public:
		Reserve()
		{
			book_id=0;
			user_id=0;
		};
		int Reserve_Book();
};
