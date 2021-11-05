# Pager-Algorithm

This pager algorithm is a demonstration of how an operating system uses paging to allocate memory to processes that require more memory than the system is capable of allocating.
The pager also features FIFO replacement so when a page in disk needs to be allocated to a frame, the pager algorithm will select the frame that has gone the longest without being used.

The pager algorithm itself can handle any datastructure, however the GUI currently only supports ints. 

You can clone this repository and open it in visual studio, or use the source code to compile it yourself.
Note: The GUI is based on Win32 apps so it is currently only supported on Windows, however the pager algorithm itself will work on any platform.
