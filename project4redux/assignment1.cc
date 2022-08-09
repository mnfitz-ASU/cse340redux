// cse340
#include "execute.h"
#include "lexer.h"
#include "main.h"
#include "parser.h"

// std
#include <memory.h>

namespace cse340 {

class Assignment1 : public MainProgram
{
private:
    int OnRun(int argc, char* argv[]) override
    {
        if (argc < 1)
        {
            std::cout << "Error: missing argument\n";
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

        //execute_program(program);

        return 0;
    }
};

/*static*/ std::unique_ptr<MainProgram> MainProgram::Make()
{
    // Assignment1* mainProgram = new Assignment1{};
    // who does the: "delete mainprogram;"??

    auto mainProgram = std::make_unique<Assignment1>();
    return mainProgram;
}

} // namespace cse340

