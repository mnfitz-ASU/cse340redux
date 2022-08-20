/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

// self
#include "main.h"

// cse340
#include "parser.h"

// std
#include <fstream>
#include <stdexcept>

namespace /*annonymous*/ { 
// Anonymous namespace 
// Use for non-exported (private to this file) entities
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#sf22-use-an-unnamed-anonymous-namespace-for-all-internalnon-exported-entities
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rs-unnamed

using namespace cse340;

class MyMainProgram : public cse340::MainProgram // is-a cse340::MainProgram
{
private:
    // OnRun() override
    // Override of virtual method defined in cse340::MainProgram
    // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c128-virtual-functions-should-specify-exactly-one-of-virtual-override-or-final
	int OnRun(int argc, char* argv[]) override 
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

} // namespace /*anonymous*/

namespace cse340 {
    
/*static*/ std::unique_ptr<MainProgram> MainProgram::Make()
{
    auto mainProgram = std::make_unique<MyMainProgram>();
    return mainProgram;
}

} // namespace cse340

int main(int argc, char* argv[])
{
    int result = 0;
    try
    {
        MyMainProgram mainProgram{};
        result = mainProgram.Run(argc, argv);
    }
    catch (const std::exception& inException)
    {
        // This exception is the base class for both std::runtime_error and std::logic_error
        // First print any what() message from known runtime error messages
        std::cerr << inException.what() << '\n';
        result = -1;
    }
    catch (...)
    {
        // Some unknown excption was thrown
        std::cerr << "Unexpected exception encountered.\n";
        result = -1;
    }
    return result;
}