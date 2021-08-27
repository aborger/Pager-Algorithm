#include "OSAPI.h"
#include <iostream>


OSAPI::OSAPI(int num_frames)
{
	std::cout << "Initiating osapi...\n";
	pageAlgo = new PageAlgo(num_frames);
}

OSAPI::~OSAPI()
{
	delete(pageAlgo);
}


// Finds free frames to give to process
Process* OSAPI::allocateProcess(int id, int processSize)
{
	return pageAlgo->createProcess(id, processSize);

}



int OSAPI::getNumFrames()
{
	return pageAlgo->getNumFrames();
}

int OSAPI::getFramePageID(int frameID)
{
	return pageAlgo->getFramePageID(frameID);
}

int OSAPI::getPageFrameID(int processID, int pageID)
{
	return pageAlgo->getPageFrameID(processID, pageID);
}


int OSAPI::getFrameProcID(int frameID)
{
	return pageAlgo->getFrameProcID(frameID);
}

bool OSAPI::isFrameAllocated(int frameID)
{
	return pageAlgo->isFrameAllocated(frameID);
}

int OSAPI::getProcessSize(int processID)
{
	return pageAlgo->getProcessSize(processID);
}




