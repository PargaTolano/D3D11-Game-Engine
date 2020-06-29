#pragma once
#ifndef WINDOWCLASS
#define WINDOWCLASS

#include <Windows.h>
#include <string>
#include <chrono>

#include "D3D.h"
#include "AppTypes.h"
#include "Input.h"

extern bool running;

LRESULT CALLBACK windowCallback(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

class Window
{
private:
	
	HWND hWindow;
    HINSTANCE hInstance;

	uint w, h;

    void (*Inputs) (void);

    void (*Update)(float);

    void (*Render) (void);

public:

    Window(uint w, uint h, std::wstring window_name) :w(w), h(h), hInstance(GetModuleHandle(NULL))
    { InitializeWindow(window_name); }

	HWND GetWindow() { return this->hWindow; }

    void Show() 
    {
        ShowWindow(hWindow, SW_SHOW);
    }

    void SetInputCallback(void(*Inputs)(void))
    {
        this->Inputs = Inputs;
    }

    void SetUpdateCallback(void(*Update)(float))
    {
        this->Update = Update;
    }

    void SetRenderCallback(void(*Render)(void))
    {
        this->Render = Render;
    }

    void Run(D3D*d3d)
    {
        running = true;

        std::chrono::time_point<std::chrono::high_resolution_clock> curr = std::chrono::high_resolution_clock::now();
        std::chrono::time_point<std::chrono::high_resolution_clock> last = curr;

        while (running)
        {
            curr = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> diftime = curr - last;


            MSG msg;
            while (PeekMessage(&msg, hWindow, 0,0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            Inputs();

            Update(diftime.count());

            d3d->StartScene();
            Render();
            d3d->EndScene();

            last = curr;
        }
    }

private:

    void InitializeWindow(std::wstring window_name)
    {
        WNDCLASSEX wc;

        ZeroMemory(&wc, sizeof(WNDCLASSEX));

        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = windowCallback;
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.lpszClassName = window_name.c_str();

        RegisterClassEx(&wc);

        RECT wr = { 0, 0, 800, 600 };
        AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

        hWindow = CreateWindowEx(NULL,
            window_name.c_str(),
            window_name.c_str(),
            WS_OVERLAPPEDWINDOW,
            100,
            100,
            wr.right - wr.left,
            wr.bottom - wr.top,
            NULL,
            NULL,
            hInstance,
            NULL);
    }

};

#endif