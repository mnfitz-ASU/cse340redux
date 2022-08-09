// cse340
#include "lexer.h"
#include "token.h"

// std
#include <array>
#include <istream>
#include <stdexcept>   // for exception, runtime_error, out_of_range

namespace { // annonymous namespace

using namespace cse340;
using TokenKind = project4::TokenKind;

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
            key += std::toupper(c);
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

// public
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
    TokenKind tokenKind = StringToTokenKind(inSpecial);
    if (tokenKind != TokenKind::ERROR)
    {
        result.mTokenKind = tokenKind;
        result.mLexeme = inSpecial;
        result.mLineNumber = mLineNumber;
    }
    return result;
}

void Lexer::PrintTokenList()
{
    // :: meaning the free function in an annonymous namespace
    ::PrintTokenList(mTokenList);
}

Token Lexer::Peek(int inLength)
{
    if (inLength <= 0) 
    {  
        // We need to throw an exception here because we cannot peek in place or to the left
        throw std::runtime_error{__FUNCTION__  ":Error: non positive argument\n"};    
    }

    const int index = mIndex + inLength - 1;
    const bool isOutOfBounds = (index > static_cast<int>((mTokenList.size())-1));
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

Token Lexer::Get()
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

        char c = mBufferInput.PeekChar();

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

        const std::string charString = {c};
        // Not a keyword/alphanumerical
        token = {StringToTokenKind(charString), mLineNumber};
        token.mLexeme = charString;
        mBufferInput.GetChar();

        if (token.mTokenKind != TokenKind::LESS)
        {
            break;
        }

        // LESS Token is special since it can represent LESS or the first half of a NOTEQUAL Token
        isEOF = ScanSpace();
        if (isEOF)
        {
            break;
        }

        c = mBufferInput.PeekChar();
        if (c != '>')
        {
            break;
        }

        // Special NOTEQUAL Token case encountered
        mBufferInput.GetChar();
        token = {TokenKind::NOTEQUAL, mLineNumber};
        token.mLexeme = "<>";

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