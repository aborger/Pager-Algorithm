#include "PageAlgo.h"
#include <stdlib.h>
#include <iostream>
#include "Process.h"
#include "MemBlock.h"
#include <fstream>
#include <string>


PageAlgo::PageAlgo(int num_frames)
{
	for (int i = 0; i < num_frames; i++)
	{
		Frame new_frame;
		frames.push_back(new_frame);
		frameUsage.push(i);
	}
}

Process* PageAlgo::createProcess(int id, int processSize)
{
	int framesAllocated = 0;
	std::vector<int> frame_ids;

	Process* new_proc = nullptr;
	while (framesAllocated < processSize)
	{
		for (int i = 0; i < frames.size(); i++)
		{
			if (framesAllocated < processSize)
			{
				if (!frames[i].isAllocated())
				{
					frame_ids.push_back(i);
					framesAllocated++;
				}
			}
			else {
				break;
			}
		}

		if (framesAllocated < processSize)
		{
			// save the rest to disk
			int pagesLeftToAllocate = processSize - framesAllocated;
			for (int i = 0; i < pagesLeftToAllocate; i++)
			{
				frame_ids.push_back(-1);
				std::ofstream out("Saved_Frames/Frame_proc" + std::to_string(id) + "_page" + std::to_string(framesAllocated) + ".txt", std::ios::out);
				out << 0;
				out.close();
				framesAllocated++;
			}
		}


		// Allocate the frames you can
		new_proc = new Process(id, frame_ids);
		for (int i = 0; i < frame_ids.size(); i++)
		{
			// Allocate process to according frames in pageAlgo
			int frameID = frame_ids[i];
			if (frameID != -1)
			{
				frames[frameID].allocateProcess(new_proc, i);
			}

		}

	}





	processes.push_back(new_proc);
	return new_proc;
}



Process* PageAlgo::getProcess(int processID)
{
	return processes[processID];
}


int PageAlgo::getNumFrames()
{
	return frames.size();
}

int PageAlgo::getFramePageID(int frameID)
{
	return frames[frameID].getPageNum();
}

int PageAlgo::getPageFrameID(int processID, int pageID)
{
	return processes[processID]->getPageFrame(pageID);
}

int PageAlgo::getFrameProcID(int frameID)
{
	return frames[frameID].getProcID();
}

int PageAlgo::getProcessSize(int processID)
{
	return processes.at(processID)->processSize();
}

int PageAlgo::isFrameAllocated(int frameID)
{
	return frames[frameID].isAllocated();
}


void PageAlgo::deallocate(LogicAddress address)
{

}



PageAlgo::~PageAlgo() {}
