
#ifndef MEMORY_TABLE_H
#define MEMORY_TABLE_H

#include "expr.h"

#include <array>
#include <vector>
#include <string>

#if 1

class MemoryTable
{
public:
	int Add(int inValue);
	void Clear();
	int GetSize();

	// Defunct
	int& ScalarValueAt(std::size_t inIndex);
	int Add(int inValue, ExprType inType); // Add new data at first available index

};

#else
class MemoryTable
{
	struct Entry
	{
		ExprType mType;
		std::size_t mMemTableIndex;
		std::array<int, kArraySize> mValue;
	};
public:
	int& ScalarValueAt(std::size_t inIndex);
	std::array<int,kArraySize>& ArrayValueAt(std::size_t inIndex);
	int Add(int inValue, ExprType inType); // Add new data at first available index
	void Clear();

	int GetSize();

private:
	std::vector<Entry> mTable{}; // has-a: Table of integers
};
#endif // #if 1

#endif //MEMORY_TABLE_H