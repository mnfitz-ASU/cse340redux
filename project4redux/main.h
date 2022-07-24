#ifndef MAIN_H
#define MAIN_H

// cse340
#include "execute.h"

// std
#include <assert.h>
#include <memory>

namespace cse340 {

class MainProgram // MainProgram utilizes NVI (Non-Virtual Interface) architecture https://en.wikipedia.org/wiki/Non-virtual_interface_pattern
{
public:
    static std::unique_ptr<MainProgram> Make();

    MainProgram() = default;
    virtual ~MainProgram() = default;
    
    // NVI: public non-virtual interface 
    int Run(int argc, char* argv[])
    {
        return OnRun(argc, argv);
    }

private:
    // NVI: private virtual implementation 
    virtual int OnRun(int argc, char* argv[]) // "= 0" means derived class must implement
    {
        assert(!"Create your own OnRun method!");
    }

}; // class MainProgram

} // namespace cse340

int main(int argc, char* argv[]);

#endif // MAIN_H