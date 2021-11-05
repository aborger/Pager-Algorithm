#include "Process.h"
#include <iostream>
#include <fstream>
#include <string>




Process::Process(int id, std::vector<int> frame_nums) 
{
	processID = id;
	for (int i = 0; i < frame_nums.size(); i++)
	{
		pageTable.push_back(frame_nums[i]);
	}
}


int Process::processSize()
{
	return pageTable.size();
}

int Process::getPageFrame(int pageID)
{
	if (pageID > pageTable.size()) {
		std::cout << "Error: Not enough space allocated to process." << std::endl;
		throw 1;
	}
	else {

		return pageTable[pageID];
	}
}

void Process::savePageToDisk(int pageID)
{
	// shows that it does not have a dedicated frame because it is on the disk
	pageTable[pageID] = -1;
}

void Process::openPageFromDisk(int pageID, int frameID)
{
	pageTable[pageID] = frameID;
}


Process::~Process() {}
