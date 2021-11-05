#pragma once
#include "MemBlock.h"
#include "PageAlgo.h"
#include <vector>


// Only necessary bec
template <typename Type>
struct memHolder
{
	MemBlock<Type> memory;
};


class OSAPI
{
public:
	OSAPI(int num_frames);
	~OSAPI();

	// This function is why osapi is seperate from pageAlgo
	template <typename Type>
	MemBlock<Type> allocate(int processID, int pageNumber)
	{
		Process* process = pageAlgo->getProcess(processID);
		MemBlock<Type> mem(pageAlgo, process, pageNumber);
		return mem;
	}

	Process* allocateProcess(int id, int processSize);

	int getNumFrames();
	int getFramePageID(int frameID);
	int getFrameProcID(int frameID);
	int getPageFrameID(int processID, int pageID);
	bool isFrameAllocated(int frameID);
	int getProcessSize(int processID);

private:
	PageAlgo* pageAlgo;
};

