#pragma once

#include "resource.h"
#include "OSAPI.h"
#include <string>

typedef std::vector<std::vector<MemBlock<int>>> MemoryBank;

void AddValToList(HWND hWnd, int listID, std::string str, int val)
{
    std::string label_str = str + " " + std::to_string(val);
    PCSTR proc_txt = const_cast<char*>(label_str.c_str());
    SendMessageA(GetDlgItem(hWnd, listID), LB_ADDSTRING, 0, (LPARAM)proc_txt);
}

void AddValToList(HWND hWnd, int listID, std::string str, int val, std::string str1, int val1)
{
    std::string label_str = str + " " + std::to_string(val) + " " + str1 + " " + std::to_string(val1);
    PCSTR proc_txt = const_cast<char*>(label_str.c_str());
    SendMessageA(GetDlgItem(hWnd, listID), LB_ADDSTRING, 0, (LPARAM)proc_txt);
}

void AddValToList(HWND hWnd, int listID, std::string str)
{
    std::string label_str = str;
    PCSTR proc_txt = const_cast<char*>(label_str.c_str());
    SendMessageA(GetDlgItem(hWnd, listID), LB_ADDSTRING, 0, (LPARAM)proc_txt);
}


void UpdateFramePages(HWND hWnd, int listBoxID, OSAPI* os)
{
    int numPagesToDelete = SendMessage(GetDlgItem(hWnd, listBoxID), LB_GETCOUNT, 0, 0);
    for (int i = 0; i < numPagesToDelete; i++)
    {
        SendMessageA(GetDlgItem(hWnd, listBoxID), LB_DELETESTRING, 0, 0);
    }
    SendMessageA(GetDlgItem(hWnd, listBoxID), WM_CREATE, 0, 0);

    for (int i = 0; i < os->getNumFrames(); i++)
    {
        if (os->isFrameAllocated(i))
        {
            int pageID = os->getFramePageID(i);
            int procID = os->getFrameProcID(i);
            AddValToList(hWnd, listBoxID, "Process", procID, "Page", pageID);
        }
        else {
            AddValToList(hWnd, listBoxID, "-");
        }
    }
}

template <typename Type>
MemBlock<Type> GetSelectedMemBlock(HWND hWnd, MemoryBank mainMemory, int process_listBoxID, int page_listBoxID)
{
    HWND procList = GetDlgItem(hWnd, process_listBoxID);
    HWND pageList = GetDlgItem(hWnd, page_listBoxID);
    int processID = (int)SendMessage(procList, LB_GETCURSEL, 0, 0);
    int pageID = (int)SendMessage(pageList, LB_GETCURSEL, 0, 0);

    MemBlock<int> memory = mainMemory.at(processID).at(pageID);
    return memory;
}
