
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
    static const char kEOF = -1;

public:
    InputBuffer() = default; // default ctor
    ~InputBuffer() = default; // default dtor

    // Returns the next available character without consuming it
    char PeekChar(); 
    /// Return and consumes the next available character from this input buffer
    char GetChar();
    /// Push the provided character back into the stream
    void UngetChar(char inChar);
    /// Push the provided string back into the stream
    void UngetString(const std::string& inString);
    /// Test if the input has been exhausted
    bool EndOfInput() const;
    /// Reset the contents of the given InputBuffer
    void Reset();

private:
    /// Safely access the contents of mStream 
    std::istream& GetStream();

    const std::istream& GetStream() const;

private:
// TRICKY: mFileStream must be declared first due to ctor initilization behaviors
    std::istream* mStream{nullptr}; // We own the stream to prevent unexpected deletions
    std::vector<char> mUngetBuffer{};
};

} // namespace cse340

#endif //INPUT_BUFFER