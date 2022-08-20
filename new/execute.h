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
    // Execute this |InstructionNode| and return pointer 
    // to next |InstructionNode| to execute
    // Returns nullptr if there is no other instructions
    InstructionNode* Execute() const;

    // Return |InstructionKind| of this node
    InstructionKind GetKind() const;

    // Return the next |InstructionNode| of this node
    InstructionNode* GetNext() const;

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