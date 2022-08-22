#include "token.h"

namespace cse340 {
namespace project2 {

/// Prefer std::unordered_map over std::map as we don't need any sorted order of keys
using KeywordDict = std::unordered_map<std::string, TokenKind>;

const KeywordDict& Token::GetKeywordDict()
{
    // static makes this function level global initialized only when first called
    static const KeywordDict sDict = 
    {
        // These are the special characters
        {"->", TokenKind::kARROW},
        {"#", TokenKind::kHASH},
        {"*", TokenKind::kSTAR}
    };

    return sDict;
}

} // namespace project2
} // namespace cse340
