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
    
using TokenKind = project4::TokenKind;

class Lexer
{
public:
// Doesn't change every time
    class Token 
    {
    public:
        //Token() = default; // Default ctor
        Token(TokenKind inTokenKind = TokenKind::END_OF_FILE, int inLineNumber = -1); // Alt ctor

        void Print();    

        std::string mLexeme{""};
        TokenKind mTokenKind{TokenKind::END_OF_FILE}; 
        int mLineNumber{-1};
    };

public:
    Lexer() = default;

    Token Peek(int inLength);
    void Load(std::istream& inStream);
    Token Get();
    
private:
    bool ScanSpace();
    std::string ScanForStringDigits();
    std::string ScanForStringAlpha();
    Token TokenFromStringDigit(std::string inDigits); 
    Token TokenFromStringAlpha(std::string inAlpha);

    Token ScanNextToken();
    /// Advances through the input string until a non-whitespace or EOF character is found. Returns true if EOF is reached.

private:
    std::vector<Token> mTokenList;
    int mLineNumber;
    int mIndex;
    InputBuffer mBufferInput;
}; // class lexer

} // namespace cse340


#endif // LEXER_H