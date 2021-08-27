#pragma once
#include <vector>


typedef std::vector<int> PageTable;

class Process
{
public:
	Process(int id, std::vector<int> frame_nums);
	~Process();

	int processID;
	int processSize();
	int getPageFrame(int pageID);
	void savePageToDisk(int pageID);
	void openPageFromDisk(int pageID, int frameID);

private:
	PageTable pageTable;
};

