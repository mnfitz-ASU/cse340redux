#ifndef CSE340_PROJECT2_TOKEN_H
#define CSE340_PROJECT2_TOKEN_H

// std
#include <string>
#include <unordered_map>

namespace cse340 {
namespace project2 {

/// Holds the complete list of every possibl tokenType we can recognize
/// Changes with each project
enum class TokenKind
{ 
    // Change me for every new assignment
    kEND_OF_FILE = 0, kARROW, kSTAR, kHASH, kID, kERROR, 
    
    // REVISIT mnfitz 20aug2022: Move kNum knowledge into token.cc
    // Not all assignments use a kNUM token, so knowledge of 
    // scanning kNUM should be moved into token.cc?
    kNUM = kERROR // SUPERHACK
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

} // namespace project2

// REVIEW mnfitz 20aug2022: Bring project2 into cse340 scope
// Seems iffy for the header file to bring the project namespace into scope
// Shouldn't the user of the header file do this in the .cc file
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#sf7-dont-write-using-namespace-at-global-scope-in-a-header-file
using namespace project2;

} // namespace cse340

#endif // CSE340_PROJECT2_TOKEN_H