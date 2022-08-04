#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdio>
#include <assert.h>
#include <fstream>

#include "inputbuf.h"

namespace cse340 {

char InputBuffer::GetChar()
{
    char result;
    if (!mUngetBuffer.empty()) 
    {
        // Read any previously ungotten chars here
        result = mUngetBuffer.back();
        mUngetBuffer.pop_back();
    } 
    else 
    {
        // Else read new characters from the stream
        result = GetStream().get();
    }
    return result;
}

void InputBuffer::UngetChar(char inChar)
{
    mUngetBuffer.push_back(inChar);
}

void InputBuffer::UngetString(std::string inString)
{
    for (char unget : inString)
    {
        UngetChar(unget);
    }
}

bool InputBuffer::EndOfInput() const
{
    // We have reached end of file if mStream is exhausted 
    // and there is no characters left to be read in the unget buffer
    const bool isEof = (GetStream().eof() && mUngetBuffer.empty());
    return isEof;
}

void InputBuffer::Reset(std::istream* inStream)
{
    mStream = inStream;
    mFileStream = {};
    mUngetBuffer = {};
}

std::istream& InputBuffer::GetStream()
{
    if (mStream == nullptr)
    {
        throw std::runtime_error{__FUNCTION__ ":ERROR: Trying to access mStream while null\n"};
    }
    return *mStream;
}

const std::istream& InputBuffer::GetStream() const
{
    if (mStream == nullptr)
    {
        throw std::runtime_error{__FUNCTION__ ":ERROR: Trying to access mStream while null\n"};
    }
    return *mStream;
}

} // namespace cse340