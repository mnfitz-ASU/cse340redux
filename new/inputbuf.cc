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

char InputBuffer::PeekChar()
{
    char result = kEOF;
    do
    {
        if (!mUngetBuffer.empty()) 
        {
            // Read any previously ungotten chars here
            result = mUngetBuffer.back();
            break;
        } 

        // Else read new characters from the stream
        if (GetStream().eof())
        {
            //assert(!"Nothing to read!");
            result = kEOF;
            break;
        }

        result = GetStream().peek();

    } while (false);
    
    return result;
}

char InputBuffer::GetChar()
{
    char result = kEOF;
    do
    {
        if (!mUngetBuffer.empty()) 
        {
            // Read any previously ungotten chars here
            result = mUngetBuffer.back();
            mUngetBuffer.pop_back();
            break;
        } 

        // Else read new characters from the stream
        if (GetStream().eof())
        {
            //assert(!"Nothing to read!");
            result = kEOF;
            break;
        }
        result = GetStream().get();

    } while (false);

    return result;
}

void InputBuffer::UngetChar(char inChar)
{
    mUngetBuffer.push_back(inChar);
}

void InputBuffer::UngetString(const std::string& inString)
{
    std::string reverseStr = inString;
    std::reverse(reverseStr.begin(), reverseStr.end());
    for (char unget : reverseStr)
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

void InputBuffer::Reset()
{
    mUngetBuffer.clear();
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