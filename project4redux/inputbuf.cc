#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cstdio>
#include <assert.h>
#include <fstream>

#include "inputbuf.h"

namespace cse340 {

InputBuffer::InputBuffer(const char* inFilename) :
    mFileStream{inFilename},
    mStream{mFileStream ? mFileStream : std::cin}
{
    // Do Nothing
}

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
        result = mStream.get();
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
    const bool isEof = (mStream.eof() && mUngetBuffer.empty());
    return isEof;
}

} // namespace cse340