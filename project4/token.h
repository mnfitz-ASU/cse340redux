/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

#ifndef TOKEN_H
#define TOKEN_H
// Header include guard:
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#sf8-use-include-guards-for-all-h-files

// std
#include <string>
#include <unordered_map>

namespace cse340 {
namespace project4 {

/// Holds the complete list of every possible tokenType we can recognize
/// Changes with each project
enum class TokenKind
{ 
    // enum class: 
    // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Renum-class
    // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Renum-caps    
    
    kEND_OF_FILE = 0,
    kVAR, kFOR, kIF, kWHILE, kSWITCH, kCASE, kDEFAULT, kINPUT, kOUTPUT, kARRAY,
    kPLUS, kMINUS, kDIV, kMULT,
    kEQUAL, kCOLON, kCOMMA, kSEMICOLON,
    kLBRAC, kRBRAC, kLPAREN, kRPAREN, kLBRACE, kRBRACE,
    kNOTEQUAL, kGREATER, kLESS,
    kNUM, kID, kERROR
};

// Define my own Keyword Dictionary type
using KeywordDict = std::unordered_map<std::string, TokenKind>;

class Token 
{
public: 
    using Kind = TokenKind;

public:
    //Token() = delete; // No default ctor()
    Token(TokenKind inTokenKind = TokenKind::kERROR, int inLineNumber = -1); // Alt ctor

    /// Print the contents of the token
    void Print();    

    /// Returns reference to the dictionary of TokenKinds
    /// and their corresponding string representation
    /// This function gets updated every new project or set of keywords
    static const KeywordDict& GetKeywordDict();

public:
    TokenKind mTokenKind{TokenKind::kEND_OF_FILE}; 
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