/*
 * Copyright (C) Matthew Fitzgerald, 2022
 *
 * CSE 340, Dr. Bazzi
 * Do not share this file with anyone
 */

#ifndef CSE340_EXECUTE_H
#define CSE340_EXECUTE_H
// Header include guard:
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#sf8-use-include-guards-for-all-h-files

//std
#include <utility>
#include <vector>

namespace cse340 {

// enum class: 
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Renum-class
// https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Renum-caps  
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
    // https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c127-a-class-with-a-virtual-function-should-have-a-virtual-or-protected-destructor
    virtual ~InstructionNode() = default;

    // Execute this |InstructionNode| and return pointer 
    // to next |InstructionNode| to execute
    // Returns nullptr if there is no other instructions
    InstructionNode* Execute() const;

    // Return |InstructionKind| of this node
    InstructionKind GetKind() const;

    // Return the next |InstructionNode| in "program sequence," 
    // returns nullptr if at end of program
    InstructionNode* GetNext() const;

    // Sets the next |InstructionNode| to follow this node in the "program sequence"
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

// AssignInstructionNode: Derived class implementing the functionality of kASSIGN instructions
class AssignInstructionNode : 
    public InstructionNode // is-a: InstructionNode
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

// NoopInstructionNode: Derived class implementing the functionality of kNOOP instructions
class NoopInstructionNode : 
    public InstructionNode // is-a: InstructionNode
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

// InputInstructionNode: Derived class implementing the functionality of kIN instructions
class InputInstructionNode : 
    public InstructionNode // is-a: InstructionNode
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

// OutputInstructionNode: Derived class implementing the functionality of kOUT instructions
class OutputInstructionNode : 
    public InstructionNode // is-a: InstructionNode
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

// CJumpInstructionNode: Derived class implementing the functionality of kCJMP instructions
class CJumpInstructionNode :
    public InstructionNode // is-a: InstructionNode
{
public:
    CJumpInstructionNode(ConditionKind inKind, int inRHSIndex1, int inRHSIndex2, InstructionNode* inTarget = nullptr) :
        InstructionNode{InstructionKind::kCJMP},
        mTarget{inTarget},
        mOperandIndex{inRHSIndex1, inRHSIndex2},
        mOp{inKind}      
    {   
        // Nothing to do
    }

    // Returns the target |InstructionNode| for this jump instruction when the condition is true
    // Returns nullptr if no jump target was ever set
    InstructionNode* GetTarget() const;
    
    // Sets the target |InstructionNode| for this CJump instruction
    // During execution, if the jump condition is true, the target |InstructionNode|  
    // is invoked, else the next instruction is invoked in "program sequence"
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

// JumpInstructionNode: Derived class implementing the functionality of kJMP instructions
class JumpInstructionNode : 
    public InstructionNode // is-a: InstructionNode
{
public:
    JumpInstructionNode(InstructionNode* inTarget) :
        InstructionNode{InstructionKind::kJMP},
        mTarget{inTarget}
    {   
        // Nothing to do
    }

    // Returns the target for this Jump instruction
    // Returns nullptr if no jump target was ever set
    InstructionNode* GetTarget() const;
    
    // Sets the target InstructionNode for this jump instruction
    // During execution, the target |InstructionNode| is always invoked
    // Because this is an unonditional jump, we never 
    // invoke next |InstructionNode| in the "program sequence"
    // (Next vs Target: This seems to be a difference from the original code)
    void SetTarget(InstructionNode* inTarget);

private:
    InstructionNode* OnExecute() const override;

private:
    InstructionNode* mTarget;
};

inline InstructionNode* JumpInstructionNode::GetTarget() const
{
    return mTarget;
}

inline void JumpInstructionNode::SetTarget(InstructionNode* inTarget)
{
    mTarget = inTarget;
}

// Executes the linked list of InstructionNodes provided by |inProgram|
void ExecuteProgram(InstructionNode* inProgram);

//---------------------------------------------------------
// You should write the following function:

} // namespace cse340

#endif // CSE340_EXECUTE_H