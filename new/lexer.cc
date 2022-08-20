/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

// self
#include "lexer.h"

// cse340
#include "token.h"

// std
#include <istream>
#include <stdexcept>   // for exception, runtime_error, out_of_range

namespace { // annonymous namespace

using namespace cse340;

// Use 'const' where possible: 
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#con1-by-default-make-objects-immutable

// FWD decls
void PrintToken(const Token& inToken);
void PrintTokenList(const std::vector<Token>& inList);
const std::string& TokenKindToString(TokenKind inTokenKind);

void PrintToken(const Token& inToken)
{
    std::cout << "{" << inToken.mLexeme << " , "
         << TokenKindToString(inToken.mTokenKind) << " , "
         << inToken.mLineNumber << "}\n";
}

void PrintTokenList(const std::vector<Token>& inList)
{
    for (Token token : inList)
    {
        PrintToken(token);
    }
}

const std::string& TokenKindToString(TokenKind inTokenKind)
{
    for (const auto& entry : Token::GetKeywordDict())
    {
    const TokenKind value = entry.second;
        if (value == inTokenKind)
        {
            const std::string& key = entry.first;
            return key;
        }
    }

    static const std::string sNotFound{};
    return sNotFound;
}

TokenKind StringToTokenKind(const std::string& inString)
{
    TokenKind tokenKind = TokenKind::ERROR;
    do
    {
        if (inString.empty())
        {
            break;
        }

        std::string key = "";
        for (char c : inString)
        {
            const int upper = std::toupper(c);
            key += static_cast<char>(upper);
        }

        const auto value = Token::GetKeywordDict().find(key);
        const bool wasFound = (value != Token::GetKeywordDict().end());
        if (wasFound)
        {
            tokenKind = value->second; 
            break;
        }

        const char firstChar = key.at(0);
        if (std::isdigit(firstChar))
        {
            // We have found a NUM token. Crash if the NUM contains alpha chars
            tokenKind = TokenKind::NUM;
            break;
        }

        if (std::isalpha(firstChar))
        {
            // We have found an ID token. IDs can contain digit chars, so no checks are required
            tokenKind = TokenKind::ID;
            break;
        }
        
        tokenKind = TokenKind::ERROR;

    } while (false);
    
    return tokenKind;
}

} // namespace

namespace cse340 {

std::string Lexer::ScanForStringDigits()
{
    std::string result = "";
    for (;;)
    {
        const char c = mBufferInput.GetChar();
        if (c == InputBuffer::kEOF)
        {
            break;
        }

        if (!std::isdigit(c))
        {
            mBufferInput.UngetChar(c);
            break;
        }

        result += c;
    }
    return result;
}

std::string Lexer::ScanForStringAlpha()
{
    std::string result = "";
    for (;;)
    {
        const char c = mBufferInput.GetChar();
        if (c == InputBuffer::kEOF)
        {
            break;
        }

        if (!std::isalpha(c))
        {
            mBufferInput.UngetChar(c);
            break;
        }

        result += c;
    }
    return result;
}

char Lexer::ScanForCharSpecial()
{
    char result = InputBuffer::kEOF;
    do    
    {
        bool isEOF = ScanSpace();
        if (isEOF)
        {
            break;
        }

        const char c = mBufferInput.PeekChar();
        if (c == InputBuffer::kEOF)
        {
            break;
        }

        if (std::isalpha(c) || std::isdigit(c) || std::isspace(c))
        {
            break;
        }

        result = mBufferInput.GetChar();

    } while (false);
    return result;
}

Token Lexer::TokenFromStringDigit(const std::string& inDigits)
{
    Token result{};
    result.mLexeme = inDigits;
    result.mLineNumber = mLineNumber;
    result.mTokenKind = TokenKind::NUM;
    return result;
}

Token Lexer::TokenFromStringAlpha(const std::string& inAlpha)
{
    Token result{};
    TokenKind tokenKind = StringToTokenKind(inAlpha);
    if (tokenKind == TokenKind::ERROR)
    {
        tokenKind = TokenKind::ID;
    }
    result.mTokenKind = tokenKind;
    result.mLexeme = inAlpha;
    result.mLineNumber = mLineNumber;
    return result;
}

Token Lexer::TokenFromStringSpecial(const std::string& inSpecial)
{
    Token result{TokenKind::ERROR};

    const TokenKind tokenKind = StringToTokenKind(inSpecial);
    
    if (tokenKind != TokenKind::ERROR)
    {
        result.mTokenKind = tokenKind;
        result.mLexeme = inSpecial; 
    }
    result.mLineNumber = mLineNumber;
    return result;
}

void Lexer::PrintTokenList()
{
    // :: meaning the free function in an annonymous namespace
    ::PrintTokenList(mTokenList);
}

Token Lexer::PeekToken(int inLength)
{
    if (inLength <= 0) 
    {  
        // We need to throw an exception here because we cannot peek in place or to the left
        throw std::invalid_argument{__FUNCTION__  ":Error: non positive argument\n"};    
    }

    const std::size_t index = static_cast<std::size_t>(mIndex + inLength - 1);
    const bool isOutOfBounds = (index > mTokenList.size()-1);
    if (isOutOfBounds) 
    { // if peeking too far
        Token token{};                        
        token.mLexeme = "";
        return token;
    } 
    else
    {
        return mTokenList.at(index);
    }
}

Token Lexer::GetToken()
{
    Token token{};
    const bool isListEmpty = mTokenList.empty();
    if (!isListEmpty)
    {
        token = mTokenList.back();
        mTokenList.pop_back();
    }   
    return token;
}

void Lexer::Load(std::istream& inStream)
{
    mBufferInput.Reset(&inStream);
    for (;;)
    {
        Token result = ScanNextToken();
        mTokenList.push_back(result);
        if (result.mTokenKind == TokenKind::END_OF_FILE) 
        {
            break;
        }
    }
    std::cout << "Read all tokens";
}

Token Lexer::ScanNextToken()
{
    Token token{TokenKind::ERROR};
    do
    {
        bool isEOF = ScanSpace();
        if (isEOF)
        {
            // Nothing to read, return an empty token
            token = {TokenKind::END_OF_FILE, mLineNumber};
            token.mLexeme = "";
            break;
        }

        const char c = mBufferInput.PeekChar();

        if (std::isdigit(c))
        {
            const std::string digitString = ScanForStringDigits();
            token = TokenFromStringDigit(digitString);
            token.mLexeme = digitString;
            break;
        }

        if (std::isalpha(c))
        {
            const std::string alphaString = ScanForStringAlpha();
            token = TokenFromStringAlpha(alphaString);
            token.mLexeme = alphaString;
            break;
        }

        // single char operators; eg. LESS
        const char specialChar1 = ScanForCharSpecial();
        if (specialChar1 == InputBuffer::kEOF)
        {
            // Not a EOF and not a known character
            break;
        }

        //std::string specialString{specialChar1, 1};
        std::string specialString = {specialChar1};
        token = TokenFromStringSpecial(specialString);

        // Yuck. Have to deal with (special case) multichar tokens
        // which alias to one another; For instance LESS and NOTEQUAL (< , <>)
        // Lookahead for double char operators; eg. NOTEQUAL

        isEOF = ScanSpace();
        if (isEOF)
        {
            // No multichar token found
            break;
        }

        const char specialChar2 = ScanForCharSpecial();
        if (specialChar2 == InputBuffer::kEOF)
        {
            break;
        }

        specialString += specialChar2;

        Token multiToken = TokenFromStringSpecial(specialString);
        if (multiToken.mTokenKind == TokenKind::ERROR)
        {
            mBufferInput.UngetChar(specialChar2);
            break;
        }

        token = multiToken;

    } while (false);

    return token;
}

// private
bool Lexer::ScanSpace()
{
    bool isEOF = false;

    for (;;)
    {
        if (mBufferInput.EndOfInput())
        {
            isEOF = true;
            break;
        }

        const char readChar = mBufferInput.GetChar();
        isEOF = (readChar == InputBuffer::kEOF);
        if (isEOF)
        {
            break;
        }
        const bool isEOL = (readChar == '\n');
        if (isEOL)
        {
            mLineNumber++;
        }

        if (!isspace(readChar))
        {
            mBufferInput.UngetChar(readChar);
            break;
        }
    }
    return isEOF;
}

}// namespace cse340