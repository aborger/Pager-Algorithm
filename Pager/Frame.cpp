#include "Frame.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define FRAME_SIZE 1 // Each frame is currently only 1 byte

Frame::Frame() {
	process = nullptr;
	pageNumber = NULL;

	frame = (void*)malloc(FRAME_SIZE);
}




bool Frame::isAllocated()
{
	return process != nullptr;

}

bool Frame::isFull()
{
	return full;
}


void Frame::allocateProcess(Process* _process, int _pageNumber)
{
	process = _process;
	pageNumber = _pageNumber;
}

int Frame::getPageNum()
{
	return pageNumber;
}

int Frame::getProcID()
{
	return process->processID;
}

void Frame::unallocate()
{
	process = nullptr;
	full = false;
}

Frame::~Frame() {
}