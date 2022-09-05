/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

#ifndef CSE340_PARSER_H
#define CSE340_PARSER_H
// Header include guard:
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#sf8-use-include-guards-for-all-h-files

// cse340
#include "lexer.h"

// std
#include <string>
#include <vector>

namespace cse340 {

class Parser 
{
public:
	Parser() = default;
	
	// Scans |inStream| for tokens and parses the resulting token list
	// Throws a |ParserSyntaxException| exception if a syntax error is detected
	void ParseProgram(std::istream& inStream);

	// Verifies that the next token consumed is equal to |inExpected|
	// If not equal to |inExpected|, throws a |cse340::ParserSyntaxException|
	Token Expect(TokenKind inExpected);

private:
	Lexer mLexer{};
};

// ParserSyntaxException: thrown by parser during syntax error
// Custom exception so you can distinguish parser syntax errors from regular runtime_errors
// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#e14-use-purpose-designed-user-defined-types-as-exceptions-not-built-in-types
class ParserSyntaxException :
	public std::runtime_error // is-a: std::runtime_error
{
public:
	ParserSyntaxException(TokenKind inExpected, const Token& inActual, const std::string& inWhat) :
		std::runtime_error(inWhat),
		mExpected{inExpected},
		mActual{inActual}
	{
		// empty
	}
	
	ParserSyntaxException(TokenKind inExpected, const Token& inActual, const char* inWhat) :
		std::runtime_error(inWhat),
		mExpected{inExpected},
		mActual{inActual}
	{
		// empty
	}

	TokenKind GetExpected() const
	{
		return mExpected;
	}

	const Token& GetActual() const
	{
		return mActual;
	}

private:
	TokenKind mExpected;
	Token mActual;
};

} // namespace cse340

#endif //CSE340_PARSER_H
