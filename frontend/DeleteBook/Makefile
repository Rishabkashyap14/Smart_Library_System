#Makefile for Return Book
CFLAGS = -g -Wall

all: remove_code_runner.o Book.o Utilities.o
	g++ $(CFLAGS) remove_code_runner.o Book.o Utilities.o -o test.out -lsqlite3

remove_code_runner.o:
	g++ -c remove_code_runner.cpp

Book.o:
	g++ -c Book.cpp

Utilities.o:
	g++ -c Utilities.cpp

clean:
	rm -f *.o *.out
