#pragma once
#include "framework.h"
#include "Windowsx.h"

#define LABEL_HEIGHT    20
#define BUTTON_WIDTH    75
#define BUTTON_HEIGHT   40

void CreateColumn(HWND hWnd, LPCWSTR labelText, int labelID,  int listID, int x, int y, int width, int height, bool visual)
{
    HWND label = CreateWindow(
        TEXT("STATIC"),
        labelText,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        x, y, width, LABEL_HEIGHT,
        hWnd, (HMENU)labelID, NULL, NULL);

    if (visual)
    {
        HWND list = CreateWindowExW(
            WS_EX_CLIENTEDGE,
            L"LISTBOX",
            NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | LBS_NOSEL,
            x, y + LABEL_HEIGHT, width, height,
            hWnd,
            (HMENU)listID,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);
    }
    else {

        HWND list = CreateWindowExW(
            WS_EX_CLIENTEDGE,
            L"LISTBOX",
            NULL,
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | LBS_NOTIFY,
            x, y + LABEL_HEIGHT, width, height,
            hWnd,
            (HMENU)listID,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
            NULL);
    }

}

void CreateNumControl(HWND hWnd, LPCWSTR labelText, int labelID, int txtID, int x, int y, int width, int height)
{
    HWND label = CreateWindow(
        TEXT("STATIC"),
        labelText,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        x, y, width, LABEL_HEIGHT,
        hWnd, (HMENU)labelID, NULL, NULL);


    HWND txtField = CreateWindowEx(
        0,
        L"EDIT",
        L"0",
        WS_BORDER | WS_CHILD | WS_VISIBLE | ES_NUMBER | ES_CENTER,
        x, y+ LABEL_HEIGHT, width, height,
        hWnd,
        (HMENU)txtID,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL);


}

void CreateButton(HWND hWnd, LPCWSTR buttonText, int buttonID, int x, int y)
{
    HWND addButton = CreateWindowEx(
        0,
        L"BUTTON",  // Predefined class; Unicode assumed 
        buttonText,      // Button text 
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
        x,         // x position 
        y,         // y position 
        BUTTON_WIDTH,        // Button width
        BUTTON_HEIGHT,        // Button height
        hWnd,     // Parent window
        (HMENU)buttonID,
        (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
        NULL
    );      // Pointer not needed.
}