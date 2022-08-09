/*
 * Copyright (C) Rida Bazzi, 2019
 *
 * Do not share this file with anyone
 */
#ifndef __PARSER_H__
#define __PARSER_H__

// project 4
#include "execute.h"
#include "expr.h"
#include "lexer.h"
#include "memorytable.h"
#include "symboltable.h"

// std
#include <list>
#include <string>
#include <vector>

class Parser 
{
public:
	Parser();

#if ENABLE_INPUT_STREAM_DEBUGGING
	Parser(std::istream& inStream);
#endif
	InstructionNode* ParseProgram();
	void ParseVarSection();
	// Parse lexer's tokenList returning a per-body InstructionNode* list in ioList
	void ParseBody(std::list<InstructionNode*>& ioList);
	void ParseIdList(); 
	void ParseStatementList();
	void ParseStatement();
	void ParseAssignStatement();
	void ParseWhileStatement();
	void ParseIfStatement();
	void ParseSwitchStatement();
	void ParseForStatement();
	void ParseOutputStatement();
	void ParseInputStatement();
	int ParsePrimary();
	std::tuple<int, ArithmeticOperatorType, int> ParseExpression();
	void ParseExpression2();
	ArithmeticOperatorType ParseOperator();
	void ParseOutput();
	void ParseInputs();
	std::tuple<int, ConditionalOperatorType, int> ParseCondition();
	ConditionalOperatorType ParseRelationOperator();
	void ParseCaseList(int inMemIndex, InstructionNode* inEndOfSwitch);
	void ParseCase(int inMemIndex, InstructionNode* inEndOfSwitch);
	void ParseDefaultCase(InstructionNode* inNode);
	void ParseNumList();

	bool CanShift(const ExprStack::Item& inItem1, const ExprStack::Item& inItem2);
	void DoShift(const ExprStack::Item& inItem);
	bool CanReduce(const ExprStack::Item& inItem1, const ExprStack::Item& inItem2);
	void DoReduce();

	void PrintExprTrees();
	void PrintErrors();

private:
    void syntax_error();
	void append_expression_error(int inLineNum);
	void append_assignment_error(int inLineNum);

	void printAssignmentErrors();
	void printExpressionErrors();

    Token expect(TokenType expected_type);
	Token PopExpect(ExprStack& ioStack, TokenType inType);
	Token NextSymbol();

	// Appends new InstructionNode onto the current InstructionNode list, 
	// and sets next pointer of previous list, if any
	void InstructionListAppend(InstructionNode* inNode);
	// Gets current InstructionNode* list
	std::list<InstructionNode*>* InstructionListGet();
	// Sets current InstructionNode* list
	void InstructionListSet(std::list<InstructionNode*>* inList);

private:
	LexicalAnalyzer mLexer{}; // Has-a: lexer
	ExprStack mExprStack{}; // Has-a: expression stack

	// SymbolTable stolen from Project 1
	SymbolTable mSymbolTable{};

	// Holds the intermediate representation of the inputted program 
	std::list<InstructionNode*> mInstructionList{};
	std::list<InstructionNode*>* mCurrentInstructionList{nullptr};

	// Task 1
	std::vector<ExprTree> mExprTrees{};

	// Task 2
	std::vector<int> mExpressionErrors{};
	std::vector<int> mAssignmentErrors{};
};

//InstructionNode* parse_generate_intermediate_representation();
InstructionNode* parse_generate_intermediate_representation(std::istream& inStream);

InstructionNode* MakeNoOpNode();
InstructionNode* MakeAssignNode(int inLhsIndex, int inRhsIndex1, ArithmeticOperatorType inOp, int inRhsIndex2);
InstructionNode* MakeOutputNode(int inVarIndex);
InstructionNode* MakeInputNode(int inVarIndex);
InstructionNode* MakeJumpNode(InstructionNode* inTarget, InstructionNode* inNext);
InstructionNode* MakeCJumpNode(ConditionalOperatorType inOperator, int inIndex1, int inIndex2, InstructionNode* inTarget, InstructionNode* inNext);

#endif //__PARSER_H__
