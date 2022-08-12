#ifndef MAIN_H
#define MAIN_H

// cse340
//#include "execute.h"

// std
#include <assert.h>
#include <memory>

namespace cse340 {

 // MainProgram utilizes NVI (Non-Virtual Interface) architecture 
 // https://en.wikipedia.org/wiki/Non-virtual_interface_pattern
class MainProgram
{
public:
    /// Creates and returns a unique pointer to the main program 
    static std::unique_ptr<MainProgram> Make();

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

} // namespace cse340

int main(int argc, char* argv[]);

#endif // MAIN_H