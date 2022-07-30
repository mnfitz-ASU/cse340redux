#ifndef LEXER_H
#define LEXER_H

// cse340
#include "inputbuf.h"

// std
#include <map>
#include <string>
#include <vector>

namespace cse340{

// Changes every time
/*
typedef enum { END_OF_FILE = 0,
    VAR, FOR, IF, WHILE, SWITCH, CASE, DEFAULT, INPUT, OUTPUT, ARRAY,
    PLUS, MINUS, DIV, MULT,
    EQUAL, COLON, COMMA, SEMICOLON,
    LBRAC, RBRAC, LPAREN, RPAREN, LBRACE, RBRACE,
    NOTEQUAL, GREATER, LESS,
    NUM, ID, ERROR
} TokenType;
*/

enum class TokenKind
{ 
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

const KeywordDict& GetKeywordDict()
{
    // static makes this function level global initialized only when first called
    static const KeywordDict sDict = 
    {
        // These are the reserved keywords 
        {"VAR", TokenKind::VAR},
        {"FOR", TokenKind::FOR},
        {"IF", TokenKind::IF},
        {"WHILE", TokenKind::WHILE},
        {"SWITCH", TokenKind::SWITCH},
        {"CASE", TokenKind::CASE},
        {"DEFAULT", TokenKind::DEFAULT},
        {"INPUT", TokenKind::INPUT},
        {"OUTPUT", TokenKind::OUTPUT},
        {"INPUT", TokenKind::INPUT},
        {"ARRAY", TokenKind::ARRAY},

        // These are the special characters
        {"+", TokenKind::PLUS},
        {"-", TokenKind::MINUS},
        {"/", TokenKind::DIV},
        {"*", TokenKind::MULT},
        {"=", TokenKind::EQUAL},
        {":", TokenKind::COLON},
        {"},", TokenKind::SEMICOLON},
        {"[", TokenKind::LBRAC},
        {"]", TokenKind::RBRAC},
        {"(", TokenKind::LPAREN},
        {")", TokenKind::RPAREN},
        {"{", TokenKind::LBRACE},
        {"}", TokenKind::RBRACE},
        {"<>", TokenKind::NOTEQUAL},
        {">", TokenKind::GREATER},
        {"<", TokenKind::LESS}
    };

    return sDict;
}

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