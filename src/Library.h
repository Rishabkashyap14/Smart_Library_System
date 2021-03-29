#include <iostream>

static int callback(void* data, int argc, char** argv, char** azColName);

class Book
{
	private:
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
