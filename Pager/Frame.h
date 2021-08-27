#pragma once
#include "Process.h"
#include <iostream>


class Frame
{
public:
	Frame();
	~Frame();

	// Currently not using block number because a frame is just one byte right now.
	// The block number would correspond to the page offset if the frame had more than just one byte
	template <typename Type>
	Type getBlock(int block_num)
	{
		Type* iptr = (Type*)frame;
		return *iptr;
	}

	// Also not using block number
	template <typename Type>
	void setBlock(Type val, int block_num)
	{
		*(Type*)frame = val;
	}

	template <typename Type>
	void fillBlock()
	{
		*(Type*)frame = 0;
		full = true;
	}

	bool isAllocated();
	bool isFull();
	void allocateProcess(Process* _process, int _pageNumber);
	int getPageNum();
	int getProcID();
	
	void unallocate();




private:
	Process* process;
	int pageNumber;
	void* frame;
	bool full;
};

