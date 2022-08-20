/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

// self
#include "execute.h"

// std
#include <array>
#include <utility>

// anonymous namespace
namespace {

using namespace cse340;

std::array<int, 1000> gMemory{};

// Derived InstructionNode implementing assignment
class AssignInstructionNode : public cse340::InstructionNode // is-a: cse340::InstructionNode
{
public:
    AssignInstructionNode::AssignInstructionNode() :
        InstructionNode{InstructionKind::kASSIGN}
    {   
        // Nothing to do
    }

private:
    InstructionNode* OnExecute() const override
    {
        int op1 = 0;
        int op2 = 0;
        int result = 0;

        switch (mOp)
        {
        case ArithmeticKind::kOPERATOR_PLUS:
            op1 = gMemory.at(mOperandIndex.first);
            op2 = gMemory.at(mOperandIndex.second);
            result = op1 + op2;
            break;
        case ArithmeticKind::kOPERATOR_MINUS:
            op1 = gMemory.at(mOperandIndex.first);
            op2 = gMemory.at(mOperandIndex.second);
            result = op1 - op2;
            break;
        case ArithmeticKind::kOPERATOR_MULT:
            op1 = gMemory.at(mOperandIndex.first);
            op2 = gMemory.at(mOperandIndex.second);
            result = op1 * op2;
            break;
        case ArithmeticKind::kOPERATOR_DIV:
            op1 = gMemory.at(mOperandIndex.first);
            op2 = gMemory.at(mOperandIndex.second);
            result = op1 / op2;
            break;
        case ArithmeticKind::kOPERATOR_NONE:
            op1 = gMemory.at(mOperandIndex.first);
            result = op1;
            break;
        }
        gMemory.at(mLHSIndex) = result;
        return GetNext();
    }

private:
    int mLHSIndex{-1};
    std::pair<int, int> mOperandIndex{-1, -1};
    
    ArithmeticKind mOp{ArithmeticKind::kOPERATOR_NONE};
};

} // namespace anonymous

namespace cse340 {

void ExecuteProgram(InstructionNode* inProgram)
{
    InstructionNode* pc = inProgram;
    while (pc != nullptr)
    {
        pc = pc->Execute();
    }
}

InstructionNode* parse_generate_intermediate_representation()
{
    // Empty for now
    return nullptr;
}

} // namespace cse340
