/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

// self
#include "parser.h"

// std
#include <assert.h>

namespace cse340 {

Token Parser::Expect(TokenKind inExpected)
{
    Token t = mLexer.GetToken();
    if (t.mTokenKind != inExpected)
	{
		const std::string what = "Syntax error! '" + t.mLexeme + "' at line: " + std::to_string(t.mLineNumber);
        throw ParserSyntaxException{what};
	}
    return t;
}

void Parser::ParseProgram(std::istream& inStream)
{
	mLexer.Load(inStream);
	//mLexer.PrintTokenList();
	
	assert(!"Add your own code here!");
}

} // namespace cse340


