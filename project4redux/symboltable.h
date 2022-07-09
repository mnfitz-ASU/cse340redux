
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "memorytable.h"
#include "expr.h"

#include <array>
#include <string>
#include <vector>

class SymbolTable
{
public:
	struct Entry
	{
		ExprType mType{ExprType::kScalar};
		std::string mName{};
		std::size_t mMemoryIndex{static_cast<std::size_t>(-1)};
		std::size_t mSymbolIndex{static_cast<std::size_t>(-1)};
	};

public:
	SymbolTable() = default;
	~SymbolTable() = default;

	// See if inName is in SymbolTable, returns its index if found, otherwise -1
	int Search(const std::string& inIdName); 

	// See if inName is in SymbolTable, add if not
	int LookUpOrAddEntry(const std::string& inIdName, ExprType inType); 

	// Add an entry if it 
	int AddEntry(const std::string& inIdName, ExprType inType);

	// Return the ExprType associated to the entry at the given index
	ExprType GetTypeForEntryAt(std::size_t inIndex) const;
	
	// Return the lexeme associated to the entry at the given index
	std::string GetNameForEntryAt(std::size_t inIndex) const;
	
	// Returns a reference to a scalar in SymbolTable's MemTable index
	int& MemoryScalarAt(std::size_t inIndex);

	// Return index into the memory table at this SymbolTable index
	int GetMemoryIndexForEntryAt(std::size_t inIndex);

	int GetSize();

	// Add TokenType::NUM with value: inInt to SymbolTable 
	// Returns the index of NUM in mMemTable
	int AddEntryForNUM(int inInt); 

private:
	// Add TokenType::ID named: inName to SymbolTable
	// Returns the index of ID in mMemTable
	int AddEntryForID(const std::string& inIdName, ExprType inType); 

private:
	std::vector<Entry> mSymTable{}; // has-a: Table of Entries
	MemoryTable mMemTable{};
};

#endif //SYMBOL_TABLE_H