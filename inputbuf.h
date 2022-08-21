/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

#ifndef INPUT_BUFFER_H
#define INPUT_BUFFER_H
// Header include guard:
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#sf8-use-include-guards-for-all-h-files

// std
#include <iostream>
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
    /// Return reference to current stream
    /// Return std::cin if no steam provided via |Reset()|
    /// Throws std::runtime_error if provided stream is invalid
    std::istream& GetStream();

    /// Return 'const' reference to current stream 
    /// Return std::cin if no steam provided via |Reset()|
    /// Throws std::runtime_error if provided stream is invalid
    const std::istream& GetStream() const;

private:
    /// Pointer to the current stream.
    /// Can be nullptr if no stream is provided
    std::istream* mStream{nullptr};
    /// Holds chars put back into the stream to be read later
    std::vector<char> mUngetBuffer{};
};

} // namespace cse340

#endif //INPUT_BUFFER_H