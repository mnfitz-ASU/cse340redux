#ifndef TOKEN_H
#define TOKEN_H

// std
#include <string>
#include <unordered_map>

namespace cse340 {
namespace project4 {

/// Holds the complete list of every possibl tokenType we can recognize
/// Changes with each project
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
using KeywordDict = std::unordered_map<std::string, TokenKind>;

class Token 
{
public: 
    using Kind = TokenKind;

public:
    //Token() = delete; // No default ctor()
    Token(TokenKind inTokenKind = TokenKind::ERROR, int inLineNumber = -1); // Alt ctor

    /// Print the contents of the token
    void Print();    

    /// Returns reference to the dictionary of TokenKinds
    /// and their corresponding string representation
    /// This function gets updated every new project or set of keywords
    static const KeywordDict& GetKeywordDict();

public:
    TokenKind mTokenKind{TokenKind::END_OF_FILE}; 
    int mLineNumber{-1};
    std::string mLexeme{""};
};

inline Token::Token(TokenKind inTokenKind, int inLineNumber) :
    mTokenKind{inTokenKind},
    mLineNumber{inLineNumber}
{
    // Nothing to do
}

} // namespace project4

// IFFY!
// Bring project4 into cse340 scope
using namespace project4;

} // namespace cse340

#endif // TOKEN_H