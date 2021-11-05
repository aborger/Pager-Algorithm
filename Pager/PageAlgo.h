#pragma once
#include "Frame.h"
#include <vector>
#include <queue>
#include <string>
#include <fstream>



class Process;

struct LogicAddress
{
	int pageNumber;
	int pageOffset;
};

class PageAlgo
{
public:
	PageAlgo(int _num_frames);
	~PageAlgo();



	Process* createProcess(int id, int processSize);
	void deallocate(LogicAddress);

	int getNumFrames();
	int getFramePageID(int frameID);
	int getPageFrameID(int processID, int pageID);
	int getFrameProcID(int frameID);
	int isFrameAllocated(int frameID);
	int getProcessSize(int processID);
	



	Process* getProcess(int processID);

	template <typename Type>
	void set(Process* process, LogicAddress address, Type val)
	{
		int frameID= process->getPageFrame(address.pageNumber);

		// If frame is in disk retrieve it
		if (frameID == -1)
		{
			frameID = freeFrame();
			frames[frameID].allocateProcess(process, address.pageNumber);
			process->openPageFromDisk(address.pageNumber, frameID);

			// Free disk space
			std::string file_name = "Saved_Frames/Frame_proc" + std::to_string(process->processID) + "_page" + std::to_string(address.pageNumber) + ".txt";
			if (remove(file_name.c_str()) != 0)
			{
				throw 1; // error deleting file
			}

		}

		// Refresh frame in frame usage
		refreshFrame(frameID);

		frames[frameID].setBlock<Type>(val, address.pageOffset);
	}

	template <typename Type>
	Type get(Process* process, LogicAddress address)
	{
		int frameID = process->getPageFrame(address.pageNumber);

		if (frameID == -1)
		{
			// if frame is in disk retrieve it
			frameID = freeFrame();
			frames[frameID].allocateProcess(process, address.pageNumber);

			// Get value from disk
			std::string fileLine;
			std::string file_name = "Saved_Frames/Frame_proc" + std::to_string(process->processID) + "_page" + std::to_string(address.pageNumber) + ".txt";
			std::ifstream memFile(file_name);
			if (memFile.is_open())
			{
				getline(memFile, fileLine);
				int value = std::stoi(fileLine);
				memFile.close();
				frames[frameID].setBlock<Type>(value, address.pageOffset);
				process->openPageFromDisk(address.pageNumber, frameID);
				if (remove(file_name.c_str()) != 0)
				{
					throw 1; // error deleting file
				}

			}
			else {
				throw 1; // couldn't open file
			}
		}

		// Refresh frame in frame usage
		refreshFrame(frameID);

		// access and return memory
		Frame temp_frame = frames[frameID];
		Type block = temp_frame.getBlock<Type>(address.pageOffset);
		return block;
	}

	template <typename Type>
	LogicAddress allocate(Process* process, int pageNumber)
	{
		LogicAddress address;
		address.pageOffset = 0; // Page offsets are currently not being used
		address.pageNumber = pageNumber;


		// Allocate
		int frameID = process->getPageFrame(pageNumber);
		if (frameID != -1)
		{

			refreshFrame(frameID);
			if (!frames[frameID].isFull())
			{
				frames[frameID].fillBlock<Type>();
			}

		}



		return address;
	}

private:
	std::vector<Frame> frames;
	std::vector<Process*> processes;
	// frameUsage is similar to a queue, it stores frame IDs, frames at the front have been used the least.
	std::queue<int> frameUsage;


	int freeFrame() 
	{
		int frameToSave = frameUsage.front();
		int processID = frames[frameToSave].getProcID();
		int pageID = frames[frameToSave].getPageNum();

		processes[processID]->savePageToDisk(pageID);
		std::ofstream out("Saved_Frames/Frame_proc" + std::to_string(processID) + "_page" + std::to_string(pageID) + ".txt", std::ios::out);
		refreshFrame(frameToSave);

		int memoryVal = frames[frameToSave].getBlock<int>(0);
		frames[frameToSave].unallocate();
		out << memoryVal << "\n";
		out.close();

		return frameToSave;
	}

	// Moves frame that was used to the back of the usage list to ensure it stays in memory
	void refreshFrame(int frameID)
	{
		while (true)
		{
			int tempFrame = frameUsage.front();
			frameUsage.pop();
			if (tempFrame != frameID)
			{
				frameUsage.push(tempFrame);
			}
			else {
				// frameID found
				frameUsage.push(tempFrame);
				break;
			}

		}
	}
};

