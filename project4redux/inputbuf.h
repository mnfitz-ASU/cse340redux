/*
 * Copyright (C) Rida Bazzi, 2017
 *
 * Do not share this file with anyone
 */
#ifndef __INPUT_BUFFER__H__
#define __INPUT_BUFFER__H__

#include <iostream>
#include <string>
#include <vector>

class InputBuffer {
  public:
  	InputBuffer() = default;
#if ENABLE_INPUT_STREAM_DEBUGGING
	InputBuffer(std::istream& inStream);
#endif
    void GetChar(char&);
    char UngetChar(char);
    std::string UngetString(std::string);
    bool EndOfInput();

  private:
    std::vector<char> input_buffer;
#if ENABLE_INPUT_STREAM_DEBUGGING
	std::istream& mStream{std::cin};
#endif
};

#if ENABLE_INPUT_STREAM_DEBUGGING
//ctor for input buffer
inline InputBuffer::InputBuffer(std::istream& inStream) :
	mStream{inStream}
{
	
}
#endif

#endif  //__INPUT_BUFFER__H__
