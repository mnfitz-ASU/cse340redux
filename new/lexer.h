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

    Token Peek(int inLength);
    void Load(std::istream& inStream);
    Token Get();
    void PrintTokenList();
    
private:
    bool ScanSpace();
    std::string ScanForStringDigits();
    std::string ScanForStringAlpha();
    Token TokenFromStringDigit(const std::string& inDigits); 
    Token TokenFromStringAlpha(const std::string& inAlpha);
    Token TokenFromStringSpecial(const std::string& inSpecial);

    Token ScanNextToken();
    /// Advances through the input string until a non-whitespace or EOF character is found. Returns true if EOF is reached.

private:
    std::vector<Token> mTokenList{};
    int mLineNumber{};
    int mIndex{};
    InputBuffer mBufferInput{};
}; // class lexer

} // namespace cse340


#endif // LEXER_H