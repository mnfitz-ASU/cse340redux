/*
 * Copyright (C) Mohsen Zohrevandi, 2017
 *               Rida Bazzi 2019
 * Do not share this file with anyone
 */
#include "execute.h"
#include "lexer.h"
#include "parser.h"
#include "execute.h"

#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>

namespace cse340 {

using namespace std;

// This should've been declared in execute.h
// We can't modify execute.h, so it's stuck here
void execute_program(struct InstructionNode * program);

#if ENABLE_INPUT_STREAM_DEBUGGING
int main(int argc, char* argv[])
{
    if (argc < 1)
    {
        cout << "Error: missing argument\n";
        return 1;
    }

    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */
	// $ ./a.out somedir/filename.txt
	// argv[0] = "./a.out"
	// argv[1] = "somedir/filename.txt"
	// argc = 2

	// TRICKY: Creating a parser also causes the parser's mLexer to take as input the char stream and generate as output a tokenList

	// Assume any argument passed on the command line (argv[1]) is "file to read"
	char* filename = (argc > 1 ? argv[1] : nullptr);
	std::ifstream fstream{filename}; 
	assert(fstream && "filename not found");
	std::istream& stream = (fstream ? fstream : std::cin);

	//Parser parser{stream};
	InstructionNode* program;
    program = parse_generate_intermediate_representation(stream);

    execute_program(program);

    return 0;
}

#endif
} // namespace cse340
