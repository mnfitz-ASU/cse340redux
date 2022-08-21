/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

#ifndef EXECUTE_H
#define EXECUTE_H
// Header include guard:
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#sf8-use-include-guards-for-all-h-files

//std
#include <utility>
#include <vector>

namespace cse340 {

enum class ArithmeticKind 
{
    kOPERATOR_NONE = 123,
    kOPERATOR_PLUS,
    kOPERATOR_MINUS,
    kOPERATOR_MULT,
    kOPERATOR_DIV
};

enum class ConditionKind 
{
    kCONDITION_GREATER = 345,
    kCONDITION_LESS,
    kCONDITION_NOTEQUAL
};

enum class InstructionKind
{
    kNOOP = 1000, // 1000: We shouldn't assume opcodes will always start at 0
    kIN,
    kOUT,
    kASSIGN,
    kCJMP,
    kJMP
};

// Base class for all derived InstructionNodes
class InstructionNode
{
public:
    // Base class with virtual methods requires virtual dtor: 
    // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c35-a-base-class-destructor-should-be-either-public-and-virtual-or-protected-and-non-virtual
    virtual ~InstructionNode() = default;

    // Execute this |InstructionNode| and return pointer 
    // to next |InstructionNode| to execute
    // Returns nullptr if there is no other instructions
    InstructionNode* Execute() const;

    // Return |InstructionKind| of this node
    InstructionKind GetKind() const;

    // Return the next |InstructionNode| of this node
    InstructionNode* GetNext() const;

    // Sets the next |InstructionNode| to follow this node in the program sequence 
    void SetNext(InstructionNode* inNext);

protected:
    InstructionNode(InstructionKind inKind); // alt ctor() can only be invoked by derived classes

private:
    // NVI: Overridable method to be provided by each derived class
    virtual InstructionNode* OnExecute() const = 0; // = 0: must be implemented by derived classes 

private:
    InstructionKind mKind;
    InstructionNode* mNext{nullptr};
};

inline InstructionNode::InstructionNode(InstructionKind inKind) :
    mKind{inKind}
{
    // Nothing to do
}

inline InstructionNode* InstructionNode::Execute() const
{
    return OnExecute();
}

inline InstructionKind InstructionNode::GetKind() const
{
    return mKind;
}

inline InstructionNode* InstructionNode::GetNext() const
{
    return mNext;
}

inline void InstructionNode::SetNext(InstructionNode* inNext)
{
    mNext = inNext;
}

class AssignInstructionNode : public InstructionNode // is-a: InstructionNode
{
public:
    AssignInstructionNode(ArithmeticKind inKind, int inLHSIndex, int inRHSIndex1, int inRHSIndex2) :
        InstructionNode{InstructionKind::kASSIGN},
        mLHSIndex{inLHSIndex},
        mOperandIndex{inRHSIndex1, inRHSIndex2},
        mOp{inKind}
    {   
        // Nothing to do
    }

private:
    InstructionNode* OnExecute() const override;

private:
    int mLHSIndex{-1};
    std::pair<int, int> mOperandIndex{-1, -1};
    ArithmeticKind mOp{ArithmeticKind::kOPERATOR_NONE};
};

class NoopInstructionNode : public InstructionNode // is-a: InstructionNode
{
public:
    NoopInstructionNode() :
        InstructionNode{InstructionKind::kNOOP}
    {   
        // Nothing to do
    }

private:
    InstructionNode* OnExecute() const override;
};

class InputInstructionNode : public InstructionNode // is-a: InstructionNode
{
public:
    InputInstructionNode(int inInputIndex) :
        InstructionNode{InstructionKind::kIN},
        mInputIndex{inInputIndex}
    {   
        // Nothing to do
    }

private:
    InstructionNode* OnExecute() const override;

private:
    int mInputIndex{-1};
    static std::vector<int> sInputs;
    static std::size_t sNextInput;
};

class OutputInstructionNode : public InstructionNode // is-a: InstructionNode
{
public:
    OutputInstructionNode(int inOutputIndex) :
        InstructionNode{InstructionKind::kOUT},
        mOutputIndex{inOutputIndex}
    {   
        // Nothing to do
    }

private:
    InstructionNode* OnExecute() const override;

private:
    int mOutputIndex{-1};
};

class CJumpInstructionNode : public InstructionNode // is-a: InstructionNode
{
public:
    CJumpInstructionNode(ConditionKind inKind, int inRHSIndex1, int inRHSIndex2, InstructionNode* inTarget) :
        InstructionNode{InstructionKind::kCJMP},
        mOp{inKind},
        mOperandIndex{inRHSIndex1, inRHSIndex2},
        mTarget{inTarget}
    {   
        // Nothing to do
    }

    InstructionNode* GetTarget() const;
    void SetTarget(InstructionNode* inTarget);

private:
    InstructionNode* OnExecute() const override;

private:
    InstructionNode* mTarget;
    std::pair<int, int> mOperandIndex{-1, -1};
    ConditionKind mOp{ConditionKind::kCONDITION_NOTEQUAL};
};

inline InstructionNode* CJumpInstructionNode::GetTarget() const
{
    return mTarget;
}

inline void CJumpInstructionNode::SetTarget(InstructionNode* inTarget)
{
    mTarget = inTarget;
}

class JumpInstructionNode : public InstructionNode // is-a: InstructionNode
{
public:
    JumpInstructionNode(InstructionNode* inTarget) :
        InstructionNode{InstructionKind::kJMP},
        mTarget{inTarget}
    {   
        // Nothing to do
    }

private:
    InstructionNode* OnExecute() const override;

private:
    InstructionNode* mTarget;
};

// Executes the linked list of InstructionNodes provided by |inProgram|
void ExecuteProgram(InstructionNode* inProgram);

//---------------------------------------------------------
// You should write the following function:

InstructionNode* parse_generate_intermediate_representation();

/*
  NOTE:

  You need to write a function with the above signature. This function
  is supposed to parse the input program and generate an intermediate
  representation for it. The output of this function is passed to the
  execute_program function in main().

  Write your code in a separate file and include this header file in
  your code.
*/

} // namespace cse340

#endif // EXECUTE_H