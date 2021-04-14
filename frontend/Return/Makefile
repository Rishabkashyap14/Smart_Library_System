#Makefile for Return Book
CFLAGS = -g -Wall

all: return_code_runner.o BookRelatedOperations.o Book.o User.o Utilities.o
	g++ $(CFLAGS) return_code_runner.o BookRelatedOperations.o Book.o User.o Utilities.o -o test.out -lsqlite3

return_code_runner.o:
	g++ -c return_code_runner.cpp

BookRelatedOperations.o:
	g++ -c BookRelatedOperations.cpp

Book.o:
	g++ -c Book.cpp

User.o:
	g++ -c User.cpp

Utilities.o:
	g++ -c Utilities.cpp

clean:
	rm -f *.o *.out
