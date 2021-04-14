#Makefile for Return Book
CFLAGS = -g -Wall -lsqlite3

all: return_code_runner.o BookRelatedOperations.o Book.o User.o Utilities.o
	g++ return_code_runner.o BookRelatedOperations.o Book.o User.o Utilities.o -o test.out $(CFLAGS)

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
