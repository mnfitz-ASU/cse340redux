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

        const int peek = GetStream().peek();
        result = static_cast<char>(peek);
        if (result == EOF)
        {
            result = kEOF;
            break;
        }

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

        const int get = GetStream().get();
        result = static_cast<char>(get);

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

void InputBuffer::Reset(std::istream* inStream)
{
    mStream = inStream;
    if (inStream != nullptr)
    {
        mStream->clear();
        mStream->seekg(0, std::ios::beg);    
    }
    
    mUngetBuffer.clear();
}

std::istream& InputBuffer::GetStream()
{
    std::istream* stream = nullptr;
    do
    {  
        if (mStream == nullptr)
        {
            stream = &std::cin;
            break;
        }

        //const bool isValid = static_cast<bool>(*mStream);
        const bool isValid = mStream->operator bool();
        if (isValid)
        {
            stream = mStream;
            break;
        }
        
        throw std::runtime_error{__FUNCTION__ ":ERROR: Trying to access invalid stream\n"};

    } while (false);

    return *stream;
}

const std::istream& InputBuffer::GetStream() const
{
    std::istream* stream = nullptr;
    do
    {  
        if (mStream == nullptr)
        {
            stream = &std::cin;
            break;
        }

        //const bool isValid = static_cast<bool>(*mStream);
        const bool isValid = mStream->operator bool();
        if (isValid)
        {
            stream = mStream;
            break;
        }
        
        throw std::runtime_error{__FUNCTION__ ":ERROR: Trying to access invalid stream\n"};

    } while (false);

    return *stream;
}

} // namespace cse340