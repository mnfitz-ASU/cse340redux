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
        {"VAR", TokenKind::kVAR},
        {"FOR", TokenKind::kFOR},
        {"IF", TokenKind::kIF},
        {"WHILE", TokenKind::kWHILE},
        {"SWITCH", TokenKind::kSWITCH},
        {"CASE", TokenKind::kCASE},
        {"DEFAULT", TokenKind::kDEFAULT},
        {"INPUT", TokenKind::kINPUT},
        {"OUTPUT", TokenKind::kOUTPUT},
        {"INPUT", TokenKind::kINPUT},
        {"ARRAY", TokenKind::kARRAY},

        // These are the special characters
        {"+", TokenKind::kPLUS},
        {"-", TokenKind::kMINUS},
        {"/", TokenKind::kDIV},
        {"*", TokenKind::kMULT},
        {"=", TokenKind::kEQUAL},
        {":", TokenKind::kCOLON},
        {",", TokenKind::kCOMMA},
        {";", TokenKind::kSEMICOLON},
        {"[", TokenKind::kLBRAC},
        {"]", TokenKind::kRBRAC},
        {"(", TokenKind::kLPAREN},
        {")", TokenKind::kRPAREN},
        {"{", TokenKind::kLBRACE},
        {"}", TokenKind::kRBRACE},
        {"<>", TokenKind::kNOTEQUAL},
        {">", TokenKind::kGREATER},
        {"<", TokenKind::kLESS}
    };

    return sDict;
}

} // namespace project4
} // namespace cse340
