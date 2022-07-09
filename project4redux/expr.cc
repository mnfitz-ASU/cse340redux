// project 4
#include "expr.h"

// std
#include <array>

int ExprStack::GetSize()
{
	return mExprStack.size();
}

void ExprStack::Push(Item inItem)
{
	mExprStack.push_back(inItem);
}

ExprStack::Item ExprStack::Pop()
{
	Item result = mExprStack.back();
	mExprStack.pop_back();
	return result;
}

ExprStack::Item& ExprStack::Top()
{
	Item& result = mExprStack.back();
	return result;
}

ExprStack::Item* ExprStack::TopTerminal()
{
	Item* result = nullptr;
	do
	{
		const int size = GetSize();
		if (GetSize() < 1)
		{
			// Fail
			result = nullptr;
			break;
		}

		result = &mExprStack.at(size-1);
		if (result->mKind == ExprKind::kTerminal)
		{
			// Success
			break;
		}

		if (GetSize() < 2)
		{
			// Fail
			result = nullptr;
			break;
		}

		result = &mExprStack.at(size-2);
		if (result->mKind == ExprKind::kTerminal)
		{
			// Success
			break;
		}

		// Fail
		result = nullptr;
		
	} while (false);
	
	return result;
}

bool ExprStack::IsEmpty()
{
	bool result = mExprStack.empty();
	return result;
}

/*static*/ int ExprPrecedence::ConvertTokenToIndex(TokenType inTokenType)
{
	int index = -1;
	switch (inTokenType)
	{
	case TokenType::PLUS:
		index = 0;
		break;

	case TokenType::MINUS:
		index = 1;
		break;
	
	case TokenType::DIV:
		index = 2;
		break;

	case TokenType::MULT:
		index = 3;
		break;
	
	case TokenType::LPAREN:
		index = 4;
		break;
	
	case TokenType::RPAREN:
		index = 5;
		break;

	case TokenType::LBRAC:
		index = 6;
		break;
	case TokenType::RBRAC:
		index = 8;
		break;

	case TokenType::NUM:
		index = 9;
		break;

	case TokenType::ID:
		index = 10;
		break;

	case TokenType::END_OF_FILE:
		index = 11;
		break;

	default:
		break;
	}
	/*
		PLUS = 4
		MINUS = 5
		DIV = 6 
		MULT = 7
		LPAREN = 12 
		RPAREN = 13
		LBRAC = 10
		DOT = 16 
		RBRAC = 11 
		NUM = 17 
		ID = 18 
		END_OF_FILE = 0
	*/
	return index;
}

/*static*/ ExprComparison ExprPrecedence::Compare(const ExprStack::Item& inItem1, const ExprStack::Item& inItem2)
{

	TokenType a = inItem1.mToken.token_type;
	TokenType b = inItem2.mToken.token_type;

	int index1 = ConvertTokenToIndex(a);
	int index2 = ConvertTokenToIndex(b);

	constexpr ExprComparison kER = ExprComparison::kERR;
	constexpr ExprComparison kGT = ExprComparison::kGT;
	constexpr ExprComparison kEQ = ExprComparison::kEQ;
	constexpr ExprComparison kLT = ExprComparison::kLT;

	static constexpr std::array<std::array<ExprComparison, 12>, 12> kOperatorPrecedence =
	{{		/* +    -    x    /   	  (    )    [    .  	  ]   NUM   ID   $ */
		/*+*/{kGT, kGT, kLT, kLT,	 kLT, kGT, kLT, kER,	 kGT, kLT, kLT, kGT},
		/*-*/{kGT, kGT, kLT, kLT,	 kLT, kGT, kLT, kER,	 kGT, kLT, kLT, kGT},
		/*x*/{kGT, kGT, kGT, kGT,	 kLT, kGT, kLT, kER,	 kGT, kLT, kLT, kGT},
		/*/*/{kGT, kGT, kGT, kGT,	 kLT, kGT, kLT, kER,	 kGT, kLT, kLT, kGT},

		/*(*/{kLT, kLT, kLT, kLT,	 kLT, kEQ, kLT, kER,	 kLT, kLT, kLT, kER},
		/*)*/{kGT, kGT, kGT, kGT,	 kER, kGT, kGT, kER,	 kGT, kER, kER, kGT},
		/*[*/{kLT, kLT, kLT, kLT,	 kLT, kLT, kLT, kEQ,	 kEQ, kLT, kLT, kER},
		/*.*/{kER, kER, kER, kER,	 kER, kER, kER, kER,	 kEQ, kER, kER, kER},

		/*]*/{kGT, kGT, kGT, kGT,	 kER, kGT, kGT, kER,	 kGT, kER, kER, kGT},
		/*#*/{kGT, kGT, kGT, kGT,	 kER, kGT, kGT, kER,	 kGT, kER, kER, kGT},
		/*I*/{kGT, kGT, kGT, kGT,	 kER, kGT, kGT, kER,	 kGT, kER, kER, kGT},
		/*$*/{kLT, kLT, kLT, kLT,	 kLT, kER, kLT, kER,	 kER, kLT, kLT, kER}
	}}; // Double brace; weird artifact of using std::array

	ExprComparison result = kOperatorPrecedence.at(index1).at(index2);	
	return result;
}

