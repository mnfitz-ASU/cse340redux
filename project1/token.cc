/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

// self
#include "token.h"

namespace cse340 {
namespace project1 {

/// Prefer std::unordered_map over std::map as we don't need any sorted order of keys
using KeywordDict = std::unordered_map<std::string, TokenKind>;

const KeywordDict& Token::GetKeywordDict()
{
    // static makes this function level global initialized only when first called
    static const KeywordDict sDict = 
    {
        // These are the reserved keywords 
        {"DO", TokenKind::kDO},
        {"ENDPROC", TokenKind::kENDPROC},
        {"INPUT", TokenKind::kINPUT},
        {"MAIN", TokenKind::kMAIN},
        {"OUTPUT", TokenKind::kOUTPUT},
        {"PROC", TokenKind::kPROC},

        // These are the special characters
        {"+", TokenKind::kPLUS},
        {"-", TokenKind::kMINUS},
        {"/", TokenKind::kDIV},
        {"*", TokenKind::kMULT},
        {"=", TokenKind::kEQUAL},
        {";", TokenKind::kSEMICOLON}
    };

    return sDict;
}

} // namespace project1
} // namespace cse340
