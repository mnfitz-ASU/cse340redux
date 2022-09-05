#
# Copyright (C) Matthew Fitzgerald, 2022
#
# CSE 340, Dr. Bazzi
# Do not share this file with anyone
#

# Location of my build
MYDIR = $(shell pwd)

# Compiled object files
MYOBJS = execute.o inputbuf.o lexer.o main.o parser.o token.o

# Subdirectory that contains project specific files
MYPROJ = project1

CC=g++
CFLAGS=-g -Wall -std=c++11 -I./$(MYPROJ)

all: a.out

clean:
	rm a.out $(MYOBJS) 

a.out: $(MYOBJS)
	$(CC) $(CFLAGS) -o a.out $(MYOBJS)

execute.o: execute.cc execute.h
	$(CC) $(CFLAGS) -c execute.cc

inputbuf.o: inputbuf.cc inputbuf.h
	$(CC) $(CFLAGS) -c inputbuf.cc

lexer.o: lexer.cc lexer.h inputbuf.h $(MYPROJ)/token.h
	$(CC) $(CFLAGS) -c lexer.cc

main.o: main.cc main.h parser.h lexer.h inputbuf.h $(MYPROJ)/token.h
	$(CC) $(CFLAGS) -c main.cc

parser.o: parser.cc parser.h lexer.h inputbuf.h $(MYPROJ)/token.h
	$(CC) $(CFLAGS) -c parser.cc

token.o: $(MYPROJ)/token.cc $(MYPROJ)/token.h 
	$(CC) $(CFLAGS) -c $(MYPROJ)/token.cc