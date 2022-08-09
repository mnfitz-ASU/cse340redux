// cse340
#include "lexer.h"
#include "token.h"

// std
#include <array>
#include <istream>
#include <stdexcept>   // for exception, runtime_error, out_of_range

// bring project4 namespace into scope
namespace cse340 {
using namespace cse340::project4;
} // namespace cse340

namespace { // annonymous namespace

using namespace cse340;
using TokenKind = project4::TokenKind;

const std::string& TokenKindToString(TokenKind inTokenKind)
{
    for (const auto& entry : GetKeywordDict())
    {
        if (entry.second == inTokenKind)
        {
            return entry.first;
        }
    }

    static const std::string sNotFound{};
    return sNotFound;
}

TokenKind StringToTokenKind(const std::string& inString)
{
    TokenKind tokenKind = TokenKind::END_OF_FILE;
    auto iter = project4::GetKeywordDict().find(inString);

    const bool wasFound = (iter != project4::GetKeywordDict().end());
    if (wasFound)
    {
        tokenKind = iter->second; // TODO: Some weird stuff is going on here. Investigate
    }
    else
    {
        for (char character : inString)
        {
            if (!isdigit(character))
            {
                tokenKind = TokenKind::ID;
                break;
            }
        }
        tokenKind = TokenKind::NUM;
    }

    return tokenKind;
}

} // namespace

namespace cse340 {

// public

std::string Lexer::ScanForStringDigits()
{
    std::string result = "";
    for (;;)
    {
        char readChar = mBufferInput.GetChar();
        if (!isdigit(readChar))
        {
            mBufferInput.UngetChar(readChar);
            break;
        }
        result += readChar;
    }
    return result;
}

std::string Lexer::ScanForStringAlpha()
{
    std::string result = "";
    for (;;)
    {
        char readChar = mBufferInput.GetChar();
        if (!isalpha(readChar))
        {
            mBufferInput.UngetChar(readChar);
            break;
        }
        result += readChar;
    }
    return result;
}

Lexer::Token Lexer::TokenFromStringDigit(std::string inDigits)
{
    Token result{};
    result.mLexeme = inDigits;
    result.mLineNumber = mLineNumber;
    result.mTokenKind = TokenKind::NUM;
    return result;
}

Lexer::Token Lexer::TokenFromStringAlpha(std::string inAlpha)
{
    Token result{};
    TokenKind tokenKind = StringToTokenKind(inAlpha);
    if (tokenKind == TokenKind::END_OF_FILE)
    {
        tokenKind = TokenKind::ID;
    }
    result.mTokenKind = tokenKind;
    result.mLexeme = inAlpha;
    result.mLineNumber = mLineNumber;
    return result;
}

Lexer::Token::Token(TokenKind inTokenKind, int inLineNumber) :
    mTokenKind{TokenKind::END_OF_FILE},
    mLineNumber{inLineNumber},
    mLexeme{""}
{
    // Do nothing
}

void Lexer::Token::Print()
{
    std::cout << "{" << this->mLexeme << " , "
         << TokenKindToString(mTokenKind) << " , "
         << this->mLineNumber << "}\n";
}

Lexer::Token Lexer::Peek(int inLength)
{
    if (inLength <= 0) 
    {  
        // We need to throw an exception here because we cannot peek in place or to the left
        throw std::runtime_error{__FUNCTION__  ":Error: non positive argument\n"};    
    }

    int peekIndex = mIndex + inLength - 1;
    if (peekIndex > (int)(mTokenList.size())-1) 
    { // if peeking too far
        Token token;                        // return END_OF_FILE
        token.mLexeme = "";
        token.mLineNumber = mLineNumber;
        token.mTokenKind = TokenKind::END_OF_FILE;
        return token;
    } else
        return mTokenList[peekIndex];
}

Lexer::Token Lexer::Get()
{
    Token token{};
    const bool isListEmpty = mTokenList.empty();
    if (!isListEmpty)
    {
        token = *mTokenList.end();
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
}

Lexer::Token Lexer::ScanNextToken()
{
    Token token{};
    char readChar;
    
    const bool isAtEOF = ScanSpace();
    if (isAtEOF)
    {
        // Nothing to read, return an empty token
        return Token{TokenKind::END_OF_FILE, mLineNumber};
    }

	// Not at end of File
    readChar = mBufferInput.GetChar();
    if (isdigit(readChar))
    {
        mBufferInput.UngetChar(readChar);
        std::string inString = ScanForStringDigits();
        return TokenFromStringDigit(inString);
    }

    // Not a digit
    if (isalpha(readChar))
    {
        // We have to check for keywords/ID
        mBufferInput.UngetChar(readChar);
        std::string inString = ScanForStringAlpha();
        return TokenFromStringAlpha(inString);
    }

    // Not a keyword/alphanumerical
    token.mTokenKind = StringToTokenKind("" + readChar);
    if (token.mTokenKind == TokenKind::LESS)
    {
        const bool isAtEnd = ScanSpace();
        if (isAtEnd)
        {
            // We have found a LESS token
            return token;
        }
        readChar = mBufferInput.GetChar();
        if (readChar == '>')
        {
            // We have found a NOTEQUAL token
            token.mTokenKind = TokenKind::NOTEQUAL;
            return token;
        }
        // We have found a LESS token
        mBufferInput.UngetChar(readChar);
        return token;
    }

    // Not a special symbol, therefore not a valid token
    token.mTokenKind = TokenKind::ERROR;
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
        mLineNumber += (readChar == '\n');

        if (!isspace(readChar))
        {
            mBufferInput.UngetChar(readChar);
            break;
        }
    }
    return isEOF;
}

}// namespace cse340