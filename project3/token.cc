/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

// self
#include "token.h"

namespace cse340 {
namespace project3 {

/// Prefer std::unordered_map over std::map as we don't need any sorted order of keys
using KeywordDict = std::unordered_map<std::string, TokenKind>;

const KeywordDict& Token::GetKeywordDict()
{
    // static makes this function level global initialized only when first called
    static const KeywordDict sDict = 
    {
#if 0
    END_OF_FILE = 0,
    SCALAR, ARRAY, OUTPUT, PLUS, MINUS, DIV, MULT,
    EQUAL, SEMICOLON,
    LBRAC, RBRAC, LPAREN, RPAREN, LBRACE, RBRACE,
    DOT, NUM, ID, ERROR
#endif
        // These are the reserved keywords 
        {"ARRAY", TokenKind::kARRAY},
        {"OUTPUT", TokenKind::kOUTPUT},
        {"SCALAR", TokenKind::kSCALAR},

        // These are the special characters
        {"+", TokenKind::kPLUS},
        {"-", TokenKind::kMINUS},
        {"/", TokenKind::kDIV},
        {"*", TokenKind::kMULT},
        {"=", TokenKind::kEQUAL},
        {";", TokenKind::kSEMICOLON},
        {"[", TokenKind::kLBRAC},
        {"]", TokenKind::kRBRAC},
        {"(", TokenKind::kLPAREN},
        {")", TokenKind::kRPAREN},
        {"{", TokenKind::kLBRACE},
        {"}", TokenKind::kRBRACE},
        {".", TokenKind::kDOT}
    };

    return sDict;
}

} // namespace project3
} // namespace cse340
