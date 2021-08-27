// Pager.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Pager.h"
#include "Windowsx.h"
#include "Column.h"
#include <string>

#define MAX_LOADSTRING 100

#define BTN_OK              201
#define BTN_ADD             202
#define BTN_SET_MEMVAL      211

#define COLUMN_TEXT         203
#define FRAME_LISTBOX       204
#define FRAMEPAGE_LISTBOX   208
#define PROCESS_LISTBOX     205
#define PAGE_LISTBOX        206
#define PROCESS_SIZE_EDITOR 207
#define PAGEFRAME_LISTBOX   209
#define PAGEVALUE_EDITOR    210

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int btn_w = 75;
int btn_h = 40;

int num_processes = 0;

OSAPI os(10);



MemoryBank mainMemory;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PAGER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAGER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAGER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PAGER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, 
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   RECT rect;
   GetWindowRect(hWnd, &rect);


    
   CreateButton(hWnd, L"Ok", BTN_OK, 1300, 625);

   CreateButton(hWnd, L"Add", BTN_ADD, 1200, 625);

   CreateButton(hWnd, L"Set", BTN_SET_MEMVAL, 700, 240);

   CreateNumControl(
       hWnd,
       TEXT("Process Size"),
       COLUMN_TEXT, PROCESS_SIZE_EDITOR,
       1100, 605, 100, btn_h
   );

   CreateNumControl(
       hWnd,
       TEXT("Memory Value"),
       COLUMN_TEXT, PAGEVALUE_EDITOR,
       600, 220, 100, btn_h
   );
   
   CreateColumn(
       hWnd,
       TEXT("Frames"), 
       COLUMN_TEXT,  FRAME_LISTBOX,
       0, 0, 100, 200,
       true
   );

   CreateColumn(
       hWnd,
       TEXT("Corresponding Page"),
       COLUMN_TEXT, FRAMEPAGE_LISTBOX,
       100, 0, 200, 200,
       true
   );

   CreateColumn(
       hWnd,
       TEXT("Process"),
       COLUMN_TEXT, PROCESS_LISTBOX,
       400, 0, 100, 200,
       false
   );

   CreateColumn(
       hWnd,
       TEXT("Pages"),
       COLUMN_TEXT, PAGE_LISTBOX,
       600, 0, 100, 200,
       false
   );

   CreateColumn(
       hWnd,
       TEXT("Corresponding Frame"),
       COLUMN_TEXT, PAGEFRAME_LISTBOX,
       700, 0, 200, 200,
       true
   );
   
   // Setup frame listbox
   for (int i = 0; i < os.getNumFrames(); i++)
   {
       AddValToList(hWnd, FRAME_LISTBOX, "Frame", i);
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Set default push button to "OK" by default
        SendMessage(hWnd, DM_SETDEFID,
                   (WPARAM)BTN_OK,
                   (LPARAM)0);
        return TRUE;
    }
    case WM_COMMAND:
    {
        // Whenever updated update frames page list
        UpdateFramePages(hWnd, FRAMEPAGE_LISTBOX, &os);

        
        // Set default push button to "ADD" when user enters text
        if (HIWORD(wParam) == EN_CHANGE && LOWORD(wParam) == PROCESS_SIZE_EDITOR)
        {
            SendMessage(hWnd, DM_SETDEFID,
                        (WPARAM) BTN_ADD,
                        (LPARAM)0);
        }
            
        int wmId = LOWORD(wParam);
        int lbId = LOWORD(lParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case BTN_ADD:
        {
            int processID = num_processes;
            UpdateFramePages(hWnd, FRAMEPAGE_LISTBOX, &os);
            // Create new process string for List Box
            BOOL success = false;
            int processSize = GetDlgItemInt(hWnd, PROCESS_SIZE_EDITOR, &success, false);

            os.allocateProcess(processID, processSize);

            // Get memory so gui can access it
            std::vector<MemBlock<int>> pageMemory;
            for (int i = 0; i < processSize; i++)
            {
                MemBlock<int> temp = os.allocate<int>(processID);
                temp = 0;
                pageMemory.push_back(temp);
            }
            mainMemory.push_back(pageMemory);


            AddValToList(hWnd, PROCESS_LISTBOX, "Process", num_processes);
            num_processes++;
            break;
        }
        case BTN_OK:
            DestroyWindow(hWnd);
            break;

        case BTN_SET_MEMVAL:
        {
            // Get MemBlock from memory and update it based on what is in the page value editor
            MemBlock<int> memory = GetSelectedMemBlock<int>(hWnd, mainMemory, PROCESS_LISTBOX, PAGE_LISTBOX);
            BOOL success = false;
            int setValue = GetDlgItemInt(hWnd, PAGEVALUE_EDITOR, &success, true);
            memory = setValue;
            break;
        }

        case PAGE_LISTBOX:
            switch (HIWORD(wParam))
            {
                case LBN_SELCHANGE:
                {
                    // Load MemBlock and display its value in the PageValue Editor
                    MemBlock<int> memory = GetSelectedMemBlock<int>(hWnd, mainMemory, PROCESS_LISTBOX, PAGE_LISTBOX);
                    std::string label_str = std::to_string(*memory);
                    LPCSTR proc_txt = const_cast<char*>(label_str.c_str());
                    SetWindowTextA(GetDlgItem(hWnd, PAGEVALUE_EDITOR), proc_txt);
                    break;
                    
                }
            }
            break;

        case PROCESS_LISTBOX:
        {
            switch (HIWORD(wParam))
            {
                case LBN_SELCHANGE:
                {
                    

                    HWND procList = GetDlgItem(hWnd, PROCESS_LISTBOX);
                    int processID = (int)SendMessage(procList, LB_GETCURSEL, 0, 0);

                    
                    int numPagesToDelete = SendMessage(GetDlgItem(hWnd, PAGE_LISTBOX), LB_GETCOUNT, 0, 0);
                    for (int i = 0; i < numPagesToDelete; i++)
                    {
                        SendMessageA(GetDlgItem(hWnd, PAGE_LISTBOX), LB_DELETESTRING, 0, 0);
                        SendMessageA(GetDlgItem(hWnd, PAGEFRAME_LISTBOX), LB_DELETESTRING, 0, 0);
                    }
                    SendMessageA(GetDlgItem(hWnd, PAGE_LISTBOX), WM_CREATE, 0, 0);

                    int numPagesToAdd = os.getProcessSize(processID);

                    // Add pages in page list box for every page in selected process
                    for (int i = 0; i < numPagesToAdd; i++)
                    {
                        AddValToList(hWnd, PAGE_LISTBOX, "Page", i);
                        AddValToList(hWnd, PAGEFRAME_LISTBOX, "Frame", os.getPageFrameID(processID, i));
                    }
                    break;
                }

            }

        }

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    /*
    case WM_SIZE:
        btn = GetWindow(hWnd, 5);
        MoveWindow(btn, rect.right - btn_dist, rect.bottom - btn_dist, btn_w, btn_h, true);
        break;
    */

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
