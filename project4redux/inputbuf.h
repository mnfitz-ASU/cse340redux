
#ifndef INPUT_BUFFER
#define INPUT_BUFFER

#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>

namespace cse340 {

class InputBuffer 
{
public:
    InputBuffer(const char* inFilename); // alt ctor
    InputBuffer() = delete; // no default ctor
    ~InputBuffer() = default; // default dtor

    /// Return the next avialable character from this input buffer
    char GetChar();
    /// Push the provided character back into the stream
    void UngetChar(char inChar);
    /// Push the provided string back into the stream
    void UngetString(std::string inString);
    /// Test if the input has been exhausted
    bool EndOfInput() const;

private:
// TRICKY: mFileStream must be declared first due to ctor initilization behaviors
    std::ifstream mFileStream;
    std::istream& mStream; // We own the stream to prevent unexpected deletions
    std::vector<char> mUngetBuffer{};
};

} // namespace cse340

#endif //INPUT_BUFFER