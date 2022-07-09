/*
 * Copyright (C) Rida Bazzi, 2022
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of
 * of this file online
 *
 */
// project 4
#include "execute.h"
#include "parser.h"

// std
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <tuple>

// Stolen from execute.h
extern std::vector<int> inputs;

void Parser::syntax_error()
{
    std::cout << "SNYATX EORRR !!!\n";
    exit(1);
}

void Parser::append_expression_error(int inLineNum)
{
	std::vector<int>::iterator find;
	find = std::find(mExpressionErrors.begin(), mExpressionErrors.end(), inLineNum);
	if (find == mExpressionErrors.end())
	{
		mExpressionErrors.push_back(inLineNum);
	}
}

void Parser::append_assignment_error(int inLineNum)
{
	std::vector<int>::iterator find;
	find = std::find(mAssignmentErrors.begin(), mAssignmentErrors.end(), inLineNum);
	if (find == mAssignmentErrors.end())
	{
		mAssignmentErrors.push_back(inLineNum);
	}	
}

// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type)
{
    Token t = mLexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

Token Parser::PopExpect(ExprStack& ioStack, TokenType inType)
{
	ExprStack::Item item = ioStack.Pop();
    if (item.mToken.token_type != inType)
        syntax_error();
    return item.mToken;
}

Token Parser::NextSymbol()
{
	Token nextSymbol = mLexer.peek(1);

	// Check out my super tricky do-while(false) statment!
	do
	{
		if (nextSymbol.token_type == TokenType::SEMICOLON)
		{
			nextSymbol.token_type = TokenType::END_OF_FILE;
			break;
		}

		if (nextSymbol.token_type == TokenType::EQUAL)
		{
			nextSymbol.token_type = TokenType::END_OF_FILE;
			break;
		}

		Token peek = mLexer.peek(2);
		if (nextSymbol.token_type == TokenType::RBRAC 
			&& peek.token_type == TokenType::EQUAL)
		{
			nextSymbol.token_type = TokenType::END_OF_FILE;
			break;
		}
	} while (false);

	return nextSymbol;
}

Parser::Parser()
{
	// Initially, stack contains $, scanning starts at the start of w
	const Token eofToken = {"$", TokenType::END_OF_FILE};
	ExprStack::Item eofItem{eofToken};
	mExprStack.Push(eofToken);
}

#if ENABLE_INPUT_STREAM_DEBUGGING
Parser::Parser(std::istream& inStream) :
	mLexer{inStream}
{
	// Initially, stack contains $, scanning starts at the start of w
	const Token eofToken = {"$", TokenType::END_OF_FILE};
	ExprStack::Item eofItem{eofToken};
	mExprStack.Push(eofToken);
}
#endif // ENABLE_INPUT_STREAM_DEBUGGING

////////////////////////////////
// Grammar Definition Section //
////////////////////////////////

InstructionNode* Parser::ParseProgram()
{
	// program → varsection body inputs
	ParseVarSection();
	ParseBody(mInstructionList); // Create an InstructionNode* list for the "main" body
	ParseInputs();
	return mInstructionList.front();
}

void Parser::ParseVarSection()
{
	// var section → idlist SEMICOLON
	ParseIdList();
	expect(TokenType::SEMICOLON);
}

void Parser::ParseBody(std::list<InstructionNode*>& ioList)
{
	// body → LBRACE stmtlist RBRACE
	// Secret Sauce: ParseBody() Creates a per-body InstructionNode* List in ioList
	std::list<InstructionNode*>* previousList = InstructionListGet(); // Save previous InstructionNode* List
	InstructionListSet(&ioList); // Set current InstructionList* List
	{
		expect(TokenType::LBRACE);
		ParseStatementList();
		expect(TokenType::RBRACE);
	}
	InstructionListSet(previousList); // Restore previous InstructionNode* List
}

void Parser::ParseIdList() 
{
	// id list → ID COMMA idlist | ID
	Token id = expect(TokenType::ID);
	int search = mSymbolTable.AddEntry(id.lexeme, ExprType::kScalar);
	if (search == -1)
	{
		syntax_error();
	}

	Token peek = mLexer.peek(1);
	if (peek.token_type == COMMA)
	{
		expect(TokenType::COMMA);
		ParseIdList();
	}
}

void Parser::ParseStatementList()
{
	// stmtlist → stmt stmtlist | stmt
	for (;;)
	{
		ParseStatement();
		Token peek = mLexer.peek(1);
		if (peek.token_type == TokenType::RBRACE)
		{
			break;
		}
	} 
}

void Parser::ParseStatement()
{
	// stmt → assignstmt | whilestmt | ifstmt | switchstmt | forstmt | outputstmt | inputstmt
	Token peek = mLexer.peek(1);
	switch (peek.token_type)
	{
	case TokenType::ID:
		ParseAssignStatement();
		break;

	case TokenType::WHILE:
		ParseWhileStatement(); // DONE
		break;

	case TokenType::SWITCH:
		ParseSwitchStatement(); // DONE
		break;

	case TokenType::FOR:
		ParseForStatement(); // DONE
		break;

	case TokenType::IF:
		ParseIfStatement(); // DONE
		break;

	case TokenType::OUTPUT:
		ParseOutputStatement(); // DONE
		break;

	case TokenType::INPUT:
		ParseInputStatement(); // DONE
		break;
	
	default:
		syntax_error();
		break;
	}	
}

void Parser::ParseAssignStatement()
{
	// InstructionNode type: Assign
	// assignstmt → ID EQUAL expr SEMICOLON
	// TODO: remember the id
	// ExprStack::Item left = mExprStack.Pop();

	Token id = expect(TokenType::ID);
	const int symIndex = mSymbolTable.Search(id.lexeme);
	if (symIndex == -1)
	{
		syntax_error();
	}
	
	const int lhsMemIndex = mSymbolTable.GetMemoryIndexForEntryAt(symIndex);
	expect(TokenType::EQUAL);

	std::tuple<int, ArithmeticOperatorType, int> expr = ParseExpression();
	// ParseExpression2();
	// ExprStack::Item right = mExprStack.Pop(); // TODO: Pop() correctly

	int rhsMemIndex1 = std::get<0>(expr);
	ArithmeticOperatorType op = std::get<1>(expr);
	int rhsMemIndex2 = std::get<2>(expr);

	// Assign represents the assignment for the statement
	InstructionNode* assign = MakeAssignNode(lhsMemIndex, rhsMemIndex1, op, rhsMemIndex2);
	InstructionListAppend(assign);

	expect(TokenType::SEMICOLON);
}

void Parser::ParseWhileStatement()
{
	// InstructionNode type: JMP
	// whilestmt → WHILE condition body
	expect(TokenType::WHILE);
	auto condition = ParseCondition();
	
	std::list<InstructionNode*> body{};
	ParseBody(body); // Create an InstructionNode* list for the body of while
	InstructionNode* target = body.front();

	int index1 = std::get<0>(condition);
	ConditionalOperatorType op = std::get<1>(condition);
	int index2 = std::get<2>(condition);

	// NoOp serves as the end of the while statement
	InstructionNode* noOp = MakeNoOpNode();
	// CJump serves as the while loop conditional jump
	InstructionNode* cJump = MakeCJumpNode(op, index1, index2, noOp, target);
	InstructionListAppend(cJump);

	// Jump serves as the end of the loop portion of the while
	InstructionNode* jump = MakeJumpNode(cJump, nullptr);
	body.back()->next = jump;
	body.push_back(jump);

	InstructionListAppend(noOp);
	body.back()->next = noOp;
}

void Parser::ParseIfStatement()
{
	// InstructionNode type: CJMP
	// ifstmt → IF condition body
	expect(TokenType::IF);
	auto condition = ParseCondition();

	std::list<InstructionNode*> body{};
	ParseBody(body); // Create an InstructionNode* list for body of if-statement
	InstructionNode* target = body.front();

	int index1 = std::get<0>(condition);
	ConditionalOperatorType op = std::get<1>(condition);
	int index2 = std::get<2>(condition);

	// NoOp serves as the end of the if statement
	InstructionNode* noOp = MakeNoOpNode();
	// CJump serves as the if statement conditional jump
	InstructionNode* cJump = MakeCJumpNode(op, index1, index2, noOp, target);
	// The PC should first encounter the conditional jump, folllowed by the noOp
	InstructionListAppend(cJump);
	InstructionListAppend(noOp);
	
	// TRICKY!!!: This is yucky because target and next are reversed for cJump!
	body.back()->next = noOp;
}

void Parser::ParseForStatement()
{
	// InstructionNode type: CJMP
	// forstmt → FOR LPAREN assign(initial) condition SEMICOLON assign(step) RPAREN body
	expect(TokenType::FOR);
	expect(TokenType::LPAREN);
	ParseAssignStatement(); // Append "initial" InstructionNode(assign) to InstructionNode list

	auto condition = ParseCondition();
	expect(TokenType::SEMICOLON);

	// Jump 1 is supposed to jump over the "step" InstructionNode(assign)
	InstructionNode* jump1 = MakeJumpNode(nullptr, nullptr);
	InstructionListAppend(jump1);

	ParseAssignStatement(); // Append "step" InstructionNode(assign) to InstructionNode list
	expect(TokenType::RPAREN);

	std::list<InstructionNode*> body{};
	ParseBody(body); // Create an InstructionNode* list for for-loop body
	InstructionNode* target = body.front();

	int index1 = std::get<0>(condition);
	ConditionalOperatorType op = std::get<1>(condition);
	int index2 = std::get<2>(condition);

	// NoOp serves as the end of the for loop statement
	InstructionNode* noOp = MakeNoOpNode();
	// CJump serves as the for loop conditional jump
	InstructionNode* cJump = MakeCJumpNode(op, index1, index2, noOp, target);
	InstructionListAppend(cJump); // Append the loop condition test; any step assignment preceedes this node
	jump1->jmp_inst.target = cJump; // jump1 skips the "step" assignment and goes directly to condition test

	InstructionListAppend(noOp); // Append end of for loop to InstructionNode* list

	InstructionNode* assignment2 = jump1->next; // Get pointer to the "step" assignment
	// Make a jump, which serves as the end of the loop, which invokes the "step" assignment
	InstructionNode* jump2 = MakeJumpNode(assignment2, nullptr);
	body.back()->next = jump2; // Add jump2 to the back of the loop body
	body.push_back(jump2); 
	body.back()->next = noOp; // Set the loop body's next to the end of the for statement
}

void Parser::ParseInputStatement()
{
	// InstructionNode type: IN
	// inputstmt → input ID SEMICOLON
	expect(TokenType::INPUT);
	Token id = expect(TokenType::ID);
	expect(TokenType::SEMICOLON);

	const int symIndex = mSymbolTable.Search(id.lexeme);
	if (symIndex == -1)
	{
		syntax_error();
	}
	
	const int memIndex = mSymbolTable.GetMemoryIndexForEntryAt(symIndex);
	InstructionListAppend(MakeInputNode(memIndex));
}

void Parser::ParseOutputStatement()
{
	// InstructionNode type: OUT
	// outputstmt → output ID SEMICOLON
	expect(TokenType::OUTPUT);
	Token id = expect(TokenType::ID);
	expect(TokenType::SEMICOLON);

	const int symIndex = mSymbolTable.Search(id.lexeme);
	if (symIndex == -1)
	{
		syntax_error();
	}
	
	const int memIndex = mSymbolTable.GetMemoryIndexForEntryAt(symIndex);
	InstructionListAppend(MakeOutputNode(memIndex));
}

int Parser::ParsePrimary()
{
	// primary → ID | NUM
	int memIndex = -1;
	Token peek = mLexer.peek(1);
	if (peek.token_type == TokenType::NUM)
	{
		expect(TokenType::NUM);
		memIndex = mSymbolTable.AddEntryForNUM(stoi(peek.lexeme));
	}
	else
	{
		expect(TokenType::ID);
		const int symIndex = mSymbolTable.Search(peek.lexeme);
		if (symIndex == -1)
		{
			syntax_error();
		}
		memIndex = mSymbolTable.GetMemoryIndexForEntryAt(symIndex);
	}
	
	return memIndex;
}

ArithmeticOperatorType Parser::ParseOperator()
{
	// op → PLUS | MINUS | MULT | DIV
	Token peek = mLexer.peek(1);
	ArithmeticOperatorType result{ArithmeticOperatorType::OPERATOR_NONE};
	switch (peek.token_type)
	{
	case TokenType::PLUS:
		expect(TokenType::PLUS);
		result = ArithmeticOperatorType::OPERATOR_PLUS;
		break;

	case TokenType::MINUS:
		expect(TokenType::MINUS);
		result = ArithmeticOperatorType::OPERATOR_MINUS;
		break;

	case TokenType::MULT:
		expect(TokenType::MULT);
		result = ArithmeticOperatorType::OPERATOR_MULT;
		break;

	case TokenType::DIV:
		expect(TokenType::DIV);
		result = ArithmeticOperatorType::OPERATOR_DIV;
		break;

	default:
		syntax_error();
		break;
	}

	return result;
}

void Parser::ParseInputs()
{
	//inputs → numlist
	ParseNumList();
}

std::tuple<int, ArithmeticOperatorType, int>  Parser::ParseExpression()
{
	//expr → primary op primary
	//expr → primary
	int primaryIndex1 = ParsePrimary();
	ArithmeticOperatorType op = ArithmeticOperatorType::OPERATOR_NONE;
	int primaryIndex2 = -1;

	Token peek = mLexer.peek(1);
	if (peek.token_type != TokenType::SEMICOLON)
	{
		op = ParseOperator();
		primaryIndex2 = ParsePrimary();
	}

	auto result = std::make_tuple(primaryIndex1, op, primaryIndex2);
	return result;
}

std::tuple<int, ConditionalOperatorType, int> Parser::ParseCondition()
{
	// condition → primary relop primary
	int index1 = ParsePrimary();
	ConditionalOperatorType op = ParseRelationOperator();
	int index2 = ParsePrimary();

	auto result = std::make_tuple(index1, op, index2);
	return result;
}

ConditionalOperatorType Parser::ParseRelationOperator()
{
	// relop → GREATER | LESS | NOTEQUAL
	Token peek = mLexer.peek(1);
	ConditionalOperatorType result{ConditionalOperatorType::CONDITION_NOTEQUAL};
	switch (peek.token_type)
	{
	case TokenType::GREATER:
		expect(TokenType::GREATER);
		result = ConditionalOperatorType::CONDITION_GREATER;
		break;

	case TokenType::LESS:
		expect(TokenType::LESS);
		result = ConditionalOperatorType::CONDITION_LESS;
		break;

	case TokenType::NOTEQUAL:
		expect(TokenType::NOTEQUAL);
		result = ConditionalOperatorType::CONDITION_NOTEQUAL;
		break;
		
	default:
		syntax_error();
		break;
	}
	return result;
}

void Parser::ParseSwitchStatement()
{
	// InstructionNode type: CJMP
	// switchstmt → SWITCH ID LBRACE caselist RBRACE
	// switchstmt → SWITCH ID LBRACE caselist defaultcase RBRACE
	expect(TokenType::SWITCH);
	Token id = expect(TokenType::ID);
	expect(TokenType::LBRACE);
	
	const int symIndex = mSymbolTable.Search(id.lexeme);
	if (symIndex == -1)
	{
		syntax_error();
	}

	// Make a node that is the end of the node which all the cases can jump to
	InstructionNode* endOfSwitch = MakeNoOpNode();

	const int memIndex = mSymbolTable.GetMemoryIndexForEntryAt(symIndex);
	ParseCaseList(memIndex, endOfSwitch);

	Token peek = mLexer.peek(1);
	if (peek.token_type != RBRACE)
	{
		ParseDefaultCase(endOfSwitch);
	}

	InstructionListAppend(endOfSwitch);
	expect(TokenType::RBRACE);
}

void Parser::ParseCaseList(int inMemIndex, InstructionNode* inEndOfSwitch)
{
	// caselist → case caselist | case
	for (;;)
	{
		ParseCase(inMemIndex, inEndOfSwitch);
		Token peek = mLexer.peek(1);
		if (peek.token_type != TokenType::CASE)
		{
			break;
		}
	} 
}

void Parser::ParseCase(int inMemIndex, InstructionNode* inEndOfSwitch)
{
	// case → CASE NUM COLON body
	expect(TokenType::CASE);
	Token num = expect(TokenType::NUM);
	expect(TokenType::COLON);
	
	int numIndex = mSymbolTable.AddEntryForNUM(stoi(num.lexeme));
	std::list<InstructionNode*> body{};
	ParseBody(body); // Create an InstructionNode* list for this body

	// NoOp is the end of the case statement 
	InstructionNode* noOp = MakeNoOpNode();
	const ConditionalOperatorType kNotEqual = ConditionalOperatorType::CONDITION_NOTEQUAL;
	// CJump is the conditional jump for this case 
	InstructionNode* cJump = MakeCJumpNode(kNotEqual, inMemIndex, numIndex, body.front(), noOp);

	InstructionListAppend(cJump); // Append the condition to the InstructionNode* list
	InstructionListAppend(noOp); // Append the NoOp as the end of the case(not taken) statement to the InstructionNode* list

	body.back()->next = inEndOfSwitch; // If case(was taken), then we have reached the end of the switch statement
}

void Parser::ParseDefaultCase(InstructionNode* inEndOfSwitch)
{
	// defaultcase → DEFAULT COLON body
	expect(TokenType::DEFAULT);
	expect(TokenType::COLON);
	
	std::list<InstructionNode*> body{};
	ParseBody(body); // Create an InstructionNode* list for this body
	InstructionNode* target = body.front();
	
	// CJump is the unconditional jump for this default case 
	InstructionNode* jump = MakeJumpNode(target, nullptr);
	InstructionListAppend(jump); // Append the jump to the current InstructionNode* list
	
	body.back()->next = inEndOfSwitch; // The end of the default body is the end of the switch statement
}

void Parser::ParseNumList()
{
	// numlist → NUM
	// numlist → NUM numlist
	for (;;)
	{
		Token num = expect(TokenType::NUM);
		inputs.push_back(stoi(num.lexeme)); // Global variable from execute.cc here

		Token peek = mLexer.peek(1);
		if (peek.token_type != TokenType::NUM)
		{
			break;
		}
	} 
}

void Parser::ParseExpression2()
{
	for (;;)
	{
		//$ is on top of the stack and lexer.peek() = $
		Token peek = NextSymbol();

		// terminal at the top of stack or just below if top is non-terminal
		ExprStack::Item* a = mExprStack.TopTerminal();
		assert(a != nullptr);
		const bool isEOFStackTop = (a->mToken.token_type == TokenType::END_OF_FILE);
		const bool isEOFNextToken = (peek.token_type == END_OF_FILE);
		if (isEOFStackTop && isEOFNextToken)
		{
			break;
		}
		
		ExprStack::Item b{peek};
		
		if (CanShift(*a, b))
		{
			DoShift(b);
		}
		else if (CanReduce(*a, b))
		{
			DoReduce();
		}
		else
		{
			append_expression_error(a->mToken.line_no);
		}
	}
}

bool Parser::CanShift(const ExprStack::Item& inItem1, const ExprStack::Item& inItem2)
{
	ExprComparison comparison = ExprPrecedence::Compare(inItem1, inItem2);
	//bool result = (table[a][b] == ‘≺∙’) | ( table[a][b] = `≐’)
	const bool canShift = (comparison == ExprComparison::kLT 
							|| comparison == ExprComparison::kEQ);
	return canShift;
}


void Parser::DoShift(const ExprStack::Item& inItem)
{
	// Tricky: Expression stack should only contain operator precedence tokens; not semi-colons
	if (inItem.mToken.token_type == TokenType::SEMICOLON 
		|| inItem.mToken.token_type == TokenType::END_OF_FILE)
	{
		syntax_error();
	}

	mExprStack.Push(inItem);

	// Only consume the token if you will return the real one, 
	// otherwise leave the fake tokens intact in mTokenList
	mLexer.GetToken();
}

bool Parser::CanReduce(const ExprStack::Item& inItem1, const ExprStack::Item& inItem2)
{
	ExprComparison comparison = ExprPrecedence::Compare(inItem1, inItem2);
	//bool result = (table[a][b] == '>')
	const bool canReduce = (comparison == ExprComparison::kGT);
	return canReduce;
}

void Parser::DoReduce()
{
	// This is E -> reduceParams
	ExprStack reduceParams{};
	ExprStack::Item lastPoppedItem{ExprKind::kNull};
	// Reduce Loop Here
	for (;;)
	{
		ExprStack::Item currentItem = mExprStack.Pop();
		
		const bool isCurrentTerminal = currentItem.IsTerminal();
		if (isCurrentTerminal)
		{
			lastPoppedItem = currentItem;
		}
		reduceParams.Push(currentItem);
		
		const bool isNextTerminal = mExprStack.Top().IsTerminal();
		if (!isNextTerminal)
		{
			continue;
		}

		const bool isNextLess = (ExprPrecedence::Compare(mExprStack.Top(), lastPoppedItem) == ExprComparison::kLT);
		if (isNextLess)
		{
			break;
		}
	} // for (;;)
	
	// Test for possible rules...
	// Reduce Id into an expression: E -> Id
	// Reduce Num into an expression: E -> Num
	// Reduce two expressions(expr operator expr) into one: E -> E + E

	assert(reduceParams.TopTerminal() != nullptr);
	ExprStack::Item* topItem = reduceParams.TopTerminal();

	switch (topItem->mToken.token_type)
	{
	case TokenType::ID:
	case TokenType::NUM:
	{
		// expr → primary

		// ID or NUM are the simplest expressions possible
		if (reduceParams.GetSize() < 1)
		{
			append_expression_error(topItem->mToken.line_no);
		}
		ExprTree::Node newNode{};
		newNode.mToken = topItem->mToken; // ID or NUM
		newNode.mType = ExprType::kScalar;

		ExprStack::Item terminal = reduceParams.Pop(); // consume the terminal
		if (!terminal.IsTerminal())
		{
			append_expression_error(topItem->mToken.line_no);
		}

		// Fill in expression with id info
		ExprStack::Item expr{ExprKind::kExpression};
		expr.mTree.SetRoot(newNode);
		mExprStack.Push(expr); // Replace the id with the expression
		break;
	}
	
	case TokenType::MULT:
	case TokenType::PLUS:
	case TokenType::MINUS:
	case TokenType::DIV:
	{
		// expr → exprL MINUS exprR
		// expr → exprL PLUS exprR
		// expr → exprL MULT exprR
		// expr → exprL DIV exprR

		// OPERATOR is a much more complex expression, since it has a left and right
		// Reduce two expressions and a terminal into one expression
		if (reduceParams.GetSize() < 3)
		{
			append_expression_error(topItem->mToken.line_no);
		}
		ExprTree::Node newNode{};
		newNode.mToken = topItem->mToken; // OPERATOR

		ExprStack::Item exprLeft = reduceParams.Pop();  // Consume exprLeft
		if (!exprLeft.IsExpression())
		{
			append_expression_error(topItem->mToken.line_no);
		}
		newNode.mLeft = exprLeft.mTree.GetRoot();

		reduceParams.Pop(); // Consume the operator

		ExprStack::Item exprRight = reduceParams.Pop();// Consume exprRight
		if (!exprRight.IsExpression())
		{
			append_expression_error(topItem->mToken.line_no);
		}
		newNode.mRight = exprRight.mTree.GetRoot(); 

		const ExprType leftType = newNode.mLeft->mType;
		const ExprType rightType = newNode.mRight->mType;
		if (leftType != rightType)
		{
			append_expression_error(topItem->mToken.line_no);
		}

		newNode.mType = newNode.mLeft->mType;

		ExprStack::Item expr{ExprKind::kExpression};
		expr.mTree.SetRoot(newNode);
		mExprStack.Push(expr); // Add the reduced expression back onto stack
		break;
	}

	case TokenType::LPAREN:
	case TokenType::RPAREN:
	{
		// expr → LPAREN expr RPAREN
		if (reduceParams.GetSize() < 3)
		{
			append_expression_error(topItem->mToken.line_no);
		}
		PopExpect(reduceParams, TokenType::LPAREN); // Consume LParen
		// Fill in expression with id info
		ExprStack::Item expr{reduceParams.Pop()}; // Consume expr
		if (!expr.IsExpression())
		{
			append_expression_error(topItem->mToken.line_no);
		} 
		PopExpect(reduceParams, TokenType::RPAREN); // Consume RParen

		mExprStack.Push(expr); // Add the reduced expression back onto stack
		break;
	}

	default:
		append_expression_error(topItem->mToken.line_no);
		break;
	}
}


// Task 1
void Parser::PrintExprTrees()
{
	if (!mExprTrees.empty())
	{
		ExprTree& expr = mExprTrees.front();
		expr.PrintTreeBFS();
	}
	
	/*
	for (ExprTree& expr : mExprTrees)
	{
		expr.PrintTreeBFS();
	}
	*/
}

// Task 2
void Parser::PrintErrors()
{
	const bool hasAssignErrors = !(mAssignmentErrors.empty());
	const bool hasExprErrors = !(mExpressionErrors.empty());

	if (hasExprErrors)
	{
		printExpressionErrors();
		return;
	}

	if (hasAssignErrors)
	{
		printAssignmentErrors();
		return;
	}
	
	std::cout << "No type errors here :)\n\n";
}

void Parser::printExpressionErrors()
{
	std::cout << "Expression type error :(\n\n";
	for (int& i : mExpressionErrors)
	{
		std::cout << "Line " << i << "\n";
	}
}

void Parser::printAssignmentErrors()
{
	std::cout << "Invalid assignment :(\n\n";
	for (int& i : mAssignmentErrors)
	{
		std::cout << "Line " << i << "\n";
	}
}

InstructionNode* parse_generate_intermediate_representation() 
{
	return parse_generate_intermediate_representation(std::cin);
}

InstructionNode* parse_generate_intermediate_representation(std::istream& inStream)
{
#if ENABLE_INPUT_STREAM_DEBUGGING
	Parser parser{inStream};
#else
	Parser parser{};
#endif
	InstructionNode* program = parser.ParseProgram();
	return program;
}

void Parser::InstructionListAppend(InstructionNode* inNode)
{
	// Check if the list is empty, if not, read previous element and set it's next to be inNode
	if (!mCurrentInstructionList->empty())
	{
		InstructionNode* tail = mCurrentInstructionList->back();
		if (tail->next == nullptr)
		{
			// Tricky: cJump instruction node reverse target and next, so we have to do this check
			tail->next = inNode;
		}
	}
	// Push inNode onto the list
	mCurrentInstructionList->push_back(inNode);
}

std::list<InstructionNode*>* Parser::InstructionListGet()
{
	return mCurrentInstructionList;
}

void Parser::InstructionListSet(std::list<InstructionNode*>* inList)
{
	mCurrentInstructionList = inList;
}

InstructionNode* MakeAssignNode(int inLhsIndex, int inRhsIndex1, ArithmeticOperatorType inOp, int inRhsIndex2)
{
	InstructionNode* newNode = new InstructionNode{};
	newNode->type = InstructionType::ASSIGN;
	newNode->next = nullptr;

	newNode->assign_inst.left_hand_side_index = inLhsIndex;
	newNode->assign_inst.operand1_index = inRhsIndex1;
	newNode->assign_inst.op = inOp;
	newNode->assign_inst.operand2_index = inRhsIndex2;

	return newNode;
}

InstructionNode* MakeNoOpNode()
{
	InstructionNode* newNode = new InstructionNode{};
	newNode->type = InstructionType::NOOP;
	newNode->next = nullptr;

	return newNode;
}


InstructionNode* MakeOutputNode(int inVarIndex)
{
	InstructionNode* newNode = new InstructionNode{};
	newNode->type = InstructionType::OUT;
	newNode->next = nullptr;

	newNode->output_inst.var_index = inVarIndex;
	return newNode;
}

InstructionNode* MakeInputNode(int inVarIndex)
{
	InstructionNode* newNode = new InstructionNode{};
	newNode->type = InstructionType::IN;
	newNode->next = nullptr;

	newNode->input_inst.var_index = inVarIndex;
	return newNode;
}

InstructionNode* MakeJumpNode(InstructionNode* inTarget, InstructionNode* inNext)
{
	InstructionNode* newNode = new InstructionNode{};
	newNode->type = InstructionType::JMP;
	newNode->next = inNext;

	newNode->jmp_inst.target = inTarget;
	return newNode;
}

InstructionNode* MakeCJumpNode(ConditionalOperatorType inOperator, int inIndex1, int inIndex2, InstructionNode* inTarget, InstructionNode* inNext)
{
	InstructionNode* newNode = new InstructionNode{};
	newNode->type = InstructionType::CJMP;
	newNode->next = inNext;

	newNode->cjmp_inst.condition_op = inOperator;
	newNode->cjmp_inst.operand1_index = inIndex1;
	newNode->cjmp_inst.operand2_index = inIndex2;
	newNode->cjmp_inst.target = inTarget;

	return newNode;
}
