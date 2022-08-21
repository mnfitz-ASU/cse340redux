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

namespace cse340 {

std::array<int, 1000> gMemory{};

// Derived InstructionNode implementing assignment

InstructionNode* AssignInstructionNode::OnExecute() const
{
    int op1 = 0;
    int op2 = 0;
    int result = 0;

    const std::size_t first = static_cast<std::size_t>(mOperandIndex.first);
    const std::size_t second = static_cast<std::size_t>(mOperandIndex.second);

    switch (mOp)
    {
    case ArithmeticKind::kOPERATOR_PLUS:
        op1 = gMemory.at(first);
        op2 = gMemory.at(second);
        result = op1 + op2;
        break;
    case ArithmeticKind::kOPERATOR_MINUS:
        op1 = gMemory.at(first);
        op2 = gMemory.at(second);
        result = op1 - op2;
        break;
    case ArithmeticKind::kOPERATOR_MULT:
        op1 = gMemory.at(first);
        op2 = gMemory.at(second);
        result = op1 * op2;
        break;
    case ArithmeticKind::kOPERATOR_DIV:
        op1 = gMemory.at(first);
        op2 = gMemory.at(second);
        result = op1 / op2;
        break;
    case ArithmeticKind::kOPERATOR_NONE:
        op1 = gMemory.at(first);
        result = op1;
        break;
    }

    const std::size_t lhsIndex = static_cast<std::size_t>(mLHSIndex);
    gMemory.at(lhsIndex) = result;
    return GetNext();
}

InstructionNode* NoopInstructionNode::OnExecute() const
{
    return GetNext();
}

/*static*/ std::vector<int> InputInstructionNode::sInputs{};
/*static*/ std::size_t InputInstructionNode::sNextInput{0};

InstructionNode* InputInstructionNode::OnExecute() const
{
    const std::size_t index = static_cast<std::size_t>(mInputIndex);
    gMemory.at(index) = sInputs.at(sNextInput);
    sNextInput++;
    return GetNext();
}

InstructionNode* CJumpInstructionNode::OnExecute() const
{
    const std::size_t first = static_cast<std::size_t>(mOperandIndex.first);
    const std::size_t second = static_cast<std::size_t>(mOperandIndex.second);

    int op1 = gMemory.at(first);
    int op2 = gMemory.at(second);

    bool isConditionTrue = false;
               
    switch (mOp)
    {
    case ConditionKind::kCONDITION_GREATER:
        isConditionTrue = (op1 > op2);
        break;
    case ConditionKind::kCONDITION_LESS:
        isConditionTrue = (op1 < op2);
        break;
    case ConditionKind::kCONDITION_NOTEQUAL:
        isConditionTrue = (op1 != op2);
        break;
    }

    // The jump target is only taken if the condition is satisfied
    InstructionNode* dest = (isConditionTrue ? mTarget : GetNext());
    return dest;
}

InstructionNode* JumpInstructionNode::OnExecute() const
{
    // The jump target is always taken
    // EG: Conditional Jump where the condition is always true
    return mTarget;
}

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
