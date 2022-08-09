// cse340
#include "main.h"
#include "assignment4.cc"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    int result = 0;
    try
    {
        auto mainProgram = cse340::MainProgram::Make();
        result = mainProgram->Run(argc, argv);
    }
    catch (const std::runtime_error& inException)
    {
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