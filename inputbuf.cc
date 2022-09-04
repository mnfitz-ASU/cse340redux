/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

// self
#include "inputbuf.h"

// std
#include <algorithm>
#include <istream>
#include <string>
#include <vector>

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

        auto& stream = GetStream();
        if (stream.eof())
        {
            result = kEOF;
            break;
        }

        const int peek = stream.peek();
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

        auto& stream = GetStream();
        if (stream.eof())
        {
            //assert(!"Nothing to read!");
            result = kEOF;
            break;
        }

        const int get = stream.get();
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

        // TRICKY mnfitz 21aug2022: std::istreams implements an "operator cast" method that  
        // returns a bool whenever the istream is used in a boolean expression.
        const bool isValid = mStream->operator bool();
        if (isValid)
        {
            stream = mStream;
            break;
        }
        
        const std::string where = __FUNCTION__;
        throw std::runtime_error{where + ":ERROR: Trying to access invalid stream\n"};

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

        // TRICKY mnfitz 21aug2022: std::istreams implements an "operator cast" method that  
        // returns a bool whenever the istream is used in a boolean expression.
        const bool isValid = mStream->operator bool();
        if (isValid)
        {
            stream = mStream;
            break;
        }
        
        throw std::runtime_error{":ERROR: Trying to access invalid stream\n"};

    } while (false);

    return *stream;
}

} // namespace cse340