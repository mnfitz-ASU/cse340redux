
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

    /// Returns the next available character without consuming it
    /// In the case there is no character, it returns |kEOF|
    char PeekChar(); 

    /// Return and consumes the next available character from this input buffer
    /// In the case there is no character, it returns |kEOF|
    char GetChar();

    /// Push the provided character back into the stream
    void UngetChar(char inChar);

    /// Push the provided string back into the stream
    void UngetString(const std::string& inString);

    /// Test if the input has been exhausted
    bool EndOfInput() const;

    /// Reset the contents of the given InputBuffer
    void Reset(std::istream* inStream = nullptr);

private:
    /// Return 'const' reference to current stream
    /// Throws a std::runtime_exception if stream is not provided
    std::istream& GetStream();

    /// Return 'const' reference to current stream without modifying its value
    /// Throws a std::runtime_exception if stream is not provided
    const std::istream& GetStream() const;

private:
    /// Pointer to the current stream.
    /// Can be nullptr if no stream is provided
    std::istream* mStream{nullptr};
    /// Holds chars put back into the stream to be read later
    std::vector<char> mUngetBuffer{};
};

} // namespace cse340

#endif //INPUT_BUFFER