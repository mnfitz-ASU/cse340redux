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

void Parser::ParseProgram(std::istream& inStream)
{
	mLexer.Load(inStream);
	mLexer.PrintTokenList();
}

} // namespace cse340


