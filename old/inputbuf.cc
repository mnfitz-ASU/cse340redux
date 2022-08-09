/*
 * Copyright (C) Rida Bazzi, 2017
 *
 * Do not share this file with anyone
 */
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cstdio>

#include "inputbuf.h"

using namespace std;

bool InputBuffer::EndOfInput()
{
    if (!input_buffer.empty())
        return false;
    else
#if ENABLE_INPUT_STREAM_DEBUGGING
		return mStream.eof();
#else
		return cin.eof();
#endif

}

char InputBuffer::UngetChar(char c)
{
    if (c != EOF)
        input_buffer.push_back(c);;
    return c;
}

void InputBuffer::GetChar(char& c)
{
    if (!input_buffer.empty()) {
        c = input_buffer.back();
        input_buffer.pop_back();
    } else {
#if ENABLE_INPUT_STREAM_DEBUGGING
		mStream.get(c);
#else
        cin.get(c);
#endif
    }
}

string InputBuffer::UngetString(string s)
{
//  for (std::size_t i = 0; i < s.size(); i++)
    for (unsigned i = 0; i < s.size(); i++)
        input_buffer.push_back(s[s.size()-i-1]);
    return s;
}
