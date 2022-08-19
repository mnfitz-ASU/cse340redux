/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

#ifndef LEXER_H
#define LEXER_H

// cse340
#include "inputbuf.h"
#include "token.h"

// std
#include <map>
#include <string>
#include <vector>

namespace cse340 {
    
class Lexer
{
public:
    Lexer() = default;

    /// Scan the provided stream and generate the |mTokenList|
    void Load(std::istream& inStream);

    /// Read the next token from |mTokenList| without consuming it
    Token PeekToken(int inLength);

    /// Read the next token from |mTokenList| and consume it
    Token GetToken();

    /// Print the contents of every token stored in |mTokenList|
    void PrintTokenList();
    
private:
    /// Advances through the input stream until a non-whitespace char or EOF is found. 
    /// Returns true if EOF is reached or there are no digits to read.
    bool ScanSpace();

    /// Reads the input stream for digit characters and returns the digit string
    /// If there are no digit chars to read, returns empty string
    std::string ScanForStringDigits();

    /// Reads the input stream for alpha characters and returns the alpha string
    /// If there are no alpha chars to read, returns empty string
    std::string ScanForStringAlpha();

    /// Reads the input stream for and returns the first special char encountered
    /// If there are no special chars to read, returns kEOF (-1)
    char ScanForCharSpecial();

    /// Creates a NUM token using the string as its lexeme
    Token TokenFromStringDigit(const std::string& inDigits);

    /// Creates a ID or keyword token using the string as its lexeme.
    Token TokenFromStringAlpha(const std::string& inAlpha);

    /// Creates a keyword token if the string corresponds to a tokenKind. 
    /// Returns an ERROR token if no TokenKind corresponds to that string
    Token TokenFromStringSpecial(const std::string& inSpecial);

    /// Reads the next token from input
    Token ScanNextToken();

private:
    /// The list of all tokens found from stream
    std::vector<Token> mTokenList{};
    /// Current GetToken/PeekToken() location in |mTokenList|
    int mIndex{0};
    /// Line number of the current token read from input
    int mLineNumber{0};
    InputBuffer mBufferInput{};
}; // class lexer

} // namespace cse340

#endif // LEXER_H