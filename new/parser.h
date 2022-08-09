/*
 * Copyright (C) Rida Bazzi, 2019
 *
 * Do not share this file with anyone
 */
#ifndef __PARSER_H__
#define __PARSER_H__

// project 4
#include "lexer.h"


// std
#include <list>
#include <string>
#include <vector>

namespace cse340 {

class Parser 
{
public:
	Parser() = default;
	void ParseProgram(std::istream& inStream);

private:
	Lexer mLexer{};
};

} // namespace cse340

#endif //__PARSER_H__
