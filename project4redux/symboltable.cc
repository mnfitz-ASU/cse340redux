#include "symboltable.h"

#include "memorytable.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

int SymbolTable::GetSize()
{
	const int size = mSymTable.size();
	return size;
}

// See if inName is in SymbolTable. If so, return symbolIndex; if not, -1
int SymbolTable::Search(const std::string& inIdName) 
{
	for (const Entry& entry : mSymTable)
	{
		if (entry.mName == inIdName)
		{
			return entry.mSymbolIndex;
		}
	}
	return -1;
}

// Add inName to SymbolTable
int SymbolTable::AddEntryForID(const std::string& inIdName, ExprType inType) 
{
	const int kDefaultValue = 0;
	const int returnIndex = mMemTable.Add(kDefaultValue, inType);
	Entry newEntry{};
	newEntry.mMemoryIndex = returnIndex;
	newEntry.mSymbolIndex = GetSize();
	newEntry.mName = inIdName;
	newEntry.mType = inType;
	mSymTable.push_back(newEntry);
	return returnIndex;
}

int SymbolTable::AddEntryForNUM(int inNum)
{
	int returnIndex = mMemTable.Add(inNum, ExprType::kScalar);
	return returnIndex;
}

// See if inName is in SymbolTable, add if not
int SymbolTable::LookUpOrAddEntry(const std::string& inIdName, ExprType inType)
{
	int index = Search(inIdName);
	const bool isFound = (index != -1);
	if (!isFound)
	{
		index = AddEntryForID(inIdName, inType);
	}
	return index;
}

// Adds a new entry to the symbolTable, returns -1 if it already exists
int SymbolTable::AddEntry(const std::string& inIdName, ExprType inType)
{
	int index = -1;
	const bool isFound = (Search(inIdName) != -1);
	if (!isFound)
	{
		index = AddEntryForID(inIdName, inType);
	}

	return index;
}

// Return the ExprType associated to the entry at the given index
ExprType SymbolTable::GetTypeForEntryAt(std::size_t inIndex) const
{
	const ExprType entryType = mSymTable.at(inIndex).mType;
	return entryType;
}

std::string SymbolTable::GetNameForEntryAt(std::size_t inIndex) const
{
	const std::string entryName = mSymTable.at(inIndex).mName;
	return entryName;
}

int SymbolTable::GetMemoryIndexForEntryAt(std::size_t inIndex)
{
	const int memIndex = mSymTable.at(inIndex).mMemoryIndex;
	return memIndex;
}

// Beware: Returning a reference to the MemoryTable instead of value
// Do this to directly modify the MemoryTable value
int& SymbolTable::MemoryScalarAt(std::size_t inIndex)
{
	return mMemTable.ScalarValueAt(inIndex);
}