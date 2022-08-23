/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

#ifndef CSE340_PROJECT4_MAIN_H
#define CSE340_PROJECT4_MAIN_H
// Header include guard:
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#sf8-use-include-guards-for-all-h-files

namespace cse340 {

 // MainProgram utilizes NVI (Non-Virtual Interface) architecture 
 // https://en.wikipedia.org/wiki/Non-virtual_interface_pattern
class MainProgram
{
public:
    // Default ctor 
    MainProgram() = default;

    // Base class with virtual methods requires virtual dtor: 
    // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c35-a-base-class-destructor-should-be-either-public-and-virtual-or-protected-and-non-virtual
    // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c127-a-class-with-a-virtual-function-should-have-a-virtual-or-protected-destructor
    virtual ~MainProgram() = default;
    
    // NVI: public non-virtual interface 
    int Run(int argc, char* argv[])
    {
        return OnRun(argc, argv);
    }

private:
    // NVI: private virtual implementation 
    virtual int OnRun(int argc, char* argv[]) = 0; // = 0; derived class must implement this
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

#endif // CSE340_PROJECT4_MAIN_H