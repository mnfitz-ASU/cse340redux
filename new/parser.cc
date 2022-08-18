/*
 * Copyright (C) Rida Bazzi, 2022
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of
 * of this file online
 *
 */
// project 4
#include "main.h"
#include "parser.h"

// std
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <tuple>

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
	mLexer.PrintTokenList();
}

} // namespace cse340


