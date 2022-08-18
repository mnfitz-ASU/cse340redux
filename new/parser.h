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
	
	// Scans |inStream| for tokens and parses the resulting token list
	void ParseProgram(std::istream& inStream);

	// Verifies that the next token consumed is equal to |inExpected|
	// If not equal to |inExpected|, throws a |ParserSyntaxException|
	Token Expect(TokenKind inExpected);

private:
	Lexer mLexer{};
};

// ParserSyntaxException: thrown by parser during syntax error
// Custom exception so you can distinguish parser syntax errors from regular runtime_errors
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e14-use-purpose-designed-user-defined-types-as-exceptions-not-built-in-types
class ParserSyntaxException : public std::runtime_error // is-a: std::runtime_error
{
public:
	ParserSyntaxException(const std::string& inWhat) :
		std::runtime_error(inWhat)
	{
		// empty
	}
	
	ParserSyntaxException(const char* inWhat) :
		std::runtime_error(inWhat)
	{
		// empty
	}
};

} // namespace cse340

#endif //__PARSER_H__
