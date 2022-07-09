#include "expr.h"
#include "memorytable.h"

#include <array>
#include <cstdlib>
#include <iostream> 
#include <fstream>

#if 1
// Stolen from execute.h
extern int mem[1000];
extern int next_available;

// Add new data at first available index
int MemoryTable::Add(int inValue)
{
	const int index = GetSize();
	mem[index] = inValue;
	next_available++;

	return index;
}

void MemoryTable::Clear()
{
	next_available = 0;
}

int MemoryTable::GetSize()
{
	return next_available;
}


// Defunct
int& MemoryTable::ScalarValueAt(std::size_t inIndex)
{
	static int dummy = -1;
	return dummy;
}

int MemoryTable::Add(int inValue, ExprType inType)
{
	return Add(inValue);
}

#else
int MemoryTable::GetSize()
{
	const int size = mTable.size();
	return size;
}

// Beware: Returning a reference to the MemoryTable instead of value
// Do this to directly modify the MemoryTable value
int& MemoryTable::ScalarValueAt(std::size_t inIndex)
{
	int& entryValue = mTable.at(inIndex).mValue.at(0);
	return entryValue;
}

// Add new data at first available index
int MemoryTable::Add(int inValue, ExprType inType)
{
	const int index = GetSize();
	Entry newEntry{};
	newEntry.mMemTableIndex = index;
	for (int& value : newEntry.mValue)
	{
		value = inValue;
	}
	
	mTable.push_back(newEntry);
	return index;
}

void MemoryTable::Clear()
{
	mTable.clear();
}


#endif