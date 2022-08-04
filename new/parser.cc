/*
 * Copyright (C) Rida Bazzi, 2022
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of
 * of this file online
 *
 */
// project 4
#include "main.h"
#include "parser.h"

// std
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <tuple>

namespace /*annonymous*/ { 

using namespace cse340;

class MainProgram4 : public MainProgram // is-a cse340::MainProgram
{
	
private:
	int OnRun(int argc, char* argv[]) override // "= 0" means derived class must implement
    {
		char* possibleFilename = nullptr;
		const bool hasPossibleFilenameArg = (argc >= 2);
		if (hasPossibleFilenameArg)
		{
			// assume the last command line arg is a filename
			const int lastCommandLineArg = argc - 1;
			possibleFilename = argv[lastCommandLineArg];
		}
		// try to open the last command line arg as a file
		std::fstream fileStream{possibleFilename}; 
		// use the stream to the file as input else read from std::cin
		std::istream& stream = (fileStream ? fileStream : std::cin);

		Parser parser{};
		parser.ParseProgram(stream);
		
		std::cout << "We did something! " << argv[0] << "\n";
	    return 0;
    }
};

} // namespace /*annonymous*/

namespace cse340 {

void Parser::ParseProgram(std::istream& inStream)
{
	// Do nothing
	mLexer.Load(inStream);
	mLexer.PrintTokenList();
}

/*static*/ std::unique_ptr<MainProgram> MainProgram::Make()
{
    // Assignment1* mainProgram = new Assignment1{};
    // who does the: "delete mainprogram;"??

    auto mainProgram = std::make_unique<MainProgram4>();
    return mainProgram;
}

} // namespace cse340


