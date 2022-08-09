#ifndef EXPR_H
#define EXPR_H

// project4
#include "lexer.h"

// std
#include <iostream>
#include <queue>
#include <vector>


// ------------------------------------------------------------------
#pragma region Project2 Stuff

namespace cse340 {

constexpr int kArraySize = 10;

enum class ExprComparison
{
	kERR,
	kGT,
	kEQ,
	kLT
};

enum class ExprKind
{
	kNull,
	kExpression,
	kTerminal
};

enum class ExprType
{
	kScalar,
	kArray
};

class ExprTree
{
public:
	struct Node
	{
		// Probably need a type here too
		Lexer::Token mToken;
		ExprType mType{ExprType::kScalar};
		Node* mLeft{nullptr};
		Node* mRight{nullptr};

		void Print() const
		{
			switch (mToken.mTokenKind)
			{
			case TokenKind::EQUAL:
				std::cout << "=";
				break;
			case TokenKind::PLUS:
				std::cout << " +";
				break;
			case TokenKind::MINUS:
				std::cout << " -";
				break;
			case TokenKind::MULT:
				std::cout << " *";
				break;
			case TokenKind::DIV:
				std::cout << " /";
				break;

			case TokenKind::LBRAC:
				std::cout << " [";
				if (mRight == nullptr)
				{
					std::cout << ".";
				}
				std::cout << "]";
				
				break;
			
			case TokenKind::ID:
				std::cout << " ID \"" << mToken.mLexeme << "\"";
				break;
			case TokenKind::NUM:
				std::cout << " NUM \"" << mToken.mLexeme << "\"";
				break;
				
			default:
				std::cout << "WE GOT SOMETHING ELSE" << mToken.mLexeme;
				break;
			}
		}
	};
public:
	Node* GetRoot();
	const Node* GetRoot() const;
	void SetRoot(const Node& inNode);
	void PrintTreeBFS() const;

private:
	void PrintChildrenBFS(const ExprTree::Node* inNode) const;

private:
	Node* mRoot{nullptr}; // Has-a: Pointer to root node

}; // class ExprTree

inline ExprTree::Node* ExprTree::GetRoot()
{
	return mRoot;
}
	
inline const ExprTree::Node* ExprTree::GetRoot() const
{
	return mRoot;
}

inline void ExprTree::SetRoot(const Node& inNode)
{
	Node* newNode = new Node{}; // Create new uninitialized node in the heap
	*newNode = inNode; // Copy the provided node to the newly created one

	mRoot = newNode; 
}

inline void ExprTree::PrintTreeBFS() const
{
	if (GetRoot() == nullptr)
	{
		return;
	}

	const ExprTree::Node* root = GetRoot();

	PrintChildrenBFS(root);
	std::cout << "\n";
}

inline void ExprTree::PrintChildrenBFS(const ExprTree::Node* inNode) const
{
#if 1
	// Note: BFS is a level ordered traversal method
	std::queue<const ExprTree::Node*> levelQueue{};
	if (inNode != nullptr)
	{
		levelQueue.push(inNode);
		while (!levelQueue.empty())
		{
			const Node* node = levelQueue.front();
			levelQueue.pop();
			node->Print(); // Print nodes at this level
			if (node->mLeft != nullptr)
			{
				levelQueue.push(node->mLeft); // queue node to print for the next level
			}
			if (node->mRight != nullptr)
			{
				levelQueue.push(node->mRight); // queue node to print for the next level
			}
		}
	}
#else
	// Print Left
	if (inNode->mLeft != nullptr)
	{
		const ExprTree::Node* node = inNode->mLeft;
		node->Print();
	}

	// Print Right
	if (inNode->mRight != nullptr)
	{
		const ExprTree::Node* node = inNode->mRight;
		node->Print();
	}

	// Traverse Left
	if (inNode->mLeft != nullptr)
	{
		PrintChildrenBFS(inNode->mLeft);
	}

	// Traverse Right
	if (inNode->mRight != nullptr)
	{
		PrintChildrenBFS(inNode->mRight);
	}
#endif
}

class ExprStack
{
public:
	struct Item
	{
		ExprKind mKind{ExprKind::kExpression};
		Lexer::Token mToken{};
		ExprTree mTree{};

		Item() = default; // Non-terminal item
		Item(Lexer::Token inToken) : // Terminal item
			mKind{ExprKind::kTerminal},
			mToken{inToken}
		{
		// Do Nothing
		}

		Item(ExprKind inKind) : 
			mKind{inKind}
		{
			// Do Nothing
		}
	
		bool IsTerminal() const
		{
			const bool result = (mKind == ExprKind::kTerminal);
			return result;
		}

		bool IsExpression() const
		{
			const bool result = (mKind == ExprKind::kExpression);
			return result;
		}
	}; // class ExprStack::Item

public:
	ExprStack() = default;
	int GetSize();
	void Push(Item inItem);
	Item Pop();
	Item& Top();
	Item* TopTerminal();
	bool IsEmpty();

private:
	std::vector<Item> mExprStack{};

};

class ExprPrecedence
{
public:
	static ExprComparison Compare(const ExprStack::Item& inItem1, const ExprStack::Item& inItem2);
private:
	static int ConvertTokenToIndex(TokenKind inTokenType);

};


} // namespace cse340


#pragma endregion

#endif // EXPR_H
