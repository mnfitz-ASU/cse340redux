#ifndef TOKEN_H
#define TOKEN_H

// std
#include <string>
#include <map>

namespace cse340 {
namespace project4 {

enum class TokenKind
{ 
    // Change me for every new assignment
    END_OF_FILE = 0,
    VAR, FOR, IF, WHILE, SWITCH, CASE, DEFAULT, INPUT, OUTPUT, ARRAY,
    PLUS, MINUS, DIV, MULT,
    EQUAL, COLON, COMMA, SEMICOLON,
    LBRAC, RBRAC, LPAREN, RPAREN, LBRACE, RBRACE,
    NOTEQUAL, GREATER, LESS,
    NUM, ID, ERROR
};

// Define my own Keyword Dictionary type
using KeywordDict = std::map<std::string, TokenKind>;

class Token 
{
public: 
    using Kind = TokenKind;

public:
    //Token() = delete; // No default ctor()
    Token(TokenKind inTokenKind = TokenKind::ERROR, int inLineNumber = -1); // Alt ctor

    void Print();    

    static const KeywordDict& GetKeywordDict();

    TokenKind mTokenKind{TokenKind::END_OF_FILE}; 
    int mLineNumber{-1};
    std::string mLexeme{""};
};

} // namespace project4

// IFFY!
// Bring project4 into cse340 scope
using namespace project4;

} // namespace cse340

#endif // TOKEN_H