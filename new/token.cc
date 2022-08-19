/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

// self
#include "token.h"

namespace cse340 {
namespace project4 {

/// Prefer std::unordered_map over std::map as we don't need any sorted order of keys
using KeywordDict = std::unordered_map<std::string, TokenKind>;

const KeywordDict& Token::GetKeywordDict()
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
        {",", TokenKind::COMMA},
        {";", TokenKind::SEMICOLON},
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

} // namespace project4
} // namespace cse340
