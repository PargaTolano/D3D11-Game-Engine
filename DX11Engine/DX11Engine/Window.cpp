#include "Window.h"

LRESULT CALLBACK windowCallback(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    if (msg == WM_KEYDOWN)  { 
        Input::getInstance().getKeyRef(wp) = true; 
    }
    if (msg == WM_KEYUP)    {
        Input::getInstance().getKeyRef(wp) = false; 
    }
    if (msg == WM_CLOSE)    { 
        running = false; 
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}