CC=g++
CFLAGS=-g -Wall -std=c++11

# Location of my build
MYDIR = $(shell pwd)

all: a.out

a.out: inputbuf.o lexer.o project4.o parser.o symboltable.o memorytable.o expr.o execute.o 
	$(CC) $(CFLAGS) -o a.out inputbuf.o lexer.o project4.o parser.o symboltable.o memorytable.o expr.o execute.o 

parser.o: parser.cc parser.h lexer.h inputbuf.h symboltable.h memorytable.h expr.h
	$(CC) $(CFLAGS) -c parser.cc

inputbuf.o: inputbuf.cc inputbuf.h
	$(CC) $(CFLAGS) -c inputbuf.cc

lexer.o: lexer.cc lexer.h inputbuf.h
	$(CC) $(CFLAGS) -c lexer.cc

symboltable.o: symboltable.cc symboltable.h memorytable.h
	$(CC) $(CFLAGS) -c symboltable.cc

memorytable.o: memorytable.cc memorytable.h
	$(CC) $(CFLAGS) -c memorytable.cc

expr.o: expr.cc expr.h
	$(CC) $(CFLAGS) -c expr.cc

execute.o: execute.cc execute.h
	$(CC) $(CFLAGS) -c execute.cc

project4.o: project4.cc parser.h lexer.h inputbuf.h memorytable.h symboltable.h execute.h 
	$(CC) $(CFLAGS) -c project4.cc

clean:
	rm parser.o inputbuf.o lexer.o symboltable.o memorytable.o expr.o execute.o project4.o a.out 
