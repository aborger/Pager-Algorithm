# Pager-Algorithm

This pager algorithm is a demonstration of how an operating system uses paging to allocate memory to processes that require more memory than the system is capable of allocating.
Currently it can allocate memory for different processes and if used as a library without the GUI, the user can allocate the memory as whatever datatype they choose (< 2 bytes). The GUI does not currently provide that option.
Currently saving frames to memory does not work perfectly. It sometimes switches frames and paging causing the wrong page to have the wrong value when it is brought back into ram from the disk.
