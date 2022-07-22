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
	  InputBuffer(std::istream& inStream);
    void GetChar(char&);
    char UngetChar(char);
    std::string UngetString(std::string);
    bool EndOfInput();

  private:
    std::vector<char> input_buffer;
	  std::istream& mStream{std::cin};
};

//ctor for input buffer
inline InputBuffer::InputBuffer(std::istream& inStream) :
  mStream{inStream}
{
	
}

#endif  //__INPUT_BUFFER__H__
