#pragma once
#include "PageAlgo.h"
#include <iostream>


template <class Type>
class MemBlock
{
public:
	MemBlock<Type>(PageAlgo* _PageAlgo, Process* _process) {
		PageAlgo = _PageAlgo;
		process = _process;
		address = PageAlgo->allocate<Type>(process);
	}
	~MemBlock<Type>() {
		PageAlgo->deallocate(address);
	}
	//~MemBlock();
	LogicAddress address;
	PageAlgo* PageAlgo;
	Process* process;

	void operator=(Type val)
	{
		PageAlgo->set<Type>(process, address, val);
	}

	Type operator*()
	{
		return PageAlgo->get<Type>(process, address);
	}

	int operator&()
	{
		int frameNum = process->getPage(address.pageNumber);
		return frameNum;
	}




};
