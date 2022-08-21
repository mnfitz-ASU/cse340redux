/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

#ifndef MAIN_H
#define MAIN_H
// Header include guard:
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#sf8-use-include-guards-for-all-h-files

// std
#include <assert.h>
#include <memory>

namespace cse340 {

 // MainProgram utilizes NVI (Non-Virtual Interface) architecture 
 // https://en.wikipedia.org/wiki/Non-virtual_interface_pattern
class MainProgram
{
public:
    /// Factory method: Creates and returns a unique pointer to the main program 
    static std::unique_ptr<MainProgram> Make();

    // Base class with virtual methods requires virtual dtor: 
    // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c35-a-base-class-destructor-should-be-either-public-and-virtual-or-protected-and-non-virtual
    virtual ~MainProgram() = default;
    
    // NVI: public non-virtual interface 
    int Run(int argc, char* argv[])
    {
        return OnRun(argc, argv);
    }

protected:
    MainProgram() = default; // Can only be used by a derived class

private:
    // NVI: private virtual implementation 
    virtual int OnRun(int /*argc*/, char*[] /*argv[]*/) 
    {
        assert(!"Create your own OnRun method!");
        return -1;
    }
}; // class MainProgram

// Class related helper function
// Returns pointer to last command line arg, or nullptr if no argument was provided
inline char* GetLastCommandLineArg(int argc, char* argv[])
{
    char* filename = nullptr;

    // we need at least 1 additional command line argument
    const bool hasPossibleFilenameArg = (argc >= 2);
    if (hasPossibleFilenameArg)
    {
        // assume the last command line arg is a filename
        const int lastCommandLineArg = argc - 1;
        filename = argv[lastCommandLineArg];
    }

    return filename;
}

} // namespace cse340

int main(int argc, char* argv[]);

#endif // MAIN_H