#include <stdlib.h>
#include<iostream>
#ifndef _INCLUDE_WINDOWS_H_
#define _INCLUDE_WINDOWS_H_
#include <Windows.h>
#endif

class Keyboard
{
    public:
        void click();
};

void Keyboard::click()
{
    INPUT input;
    // buffer.type = INPUT_KEYBOARD;
    // buffer.ki.wVk = 0x46;
    // SendInput(1, &buffer, sizeof(INPUT));
    // Sleep(500);
    // buffer.ki.dwFlags = KEYEVENTF_KEYUP;
    // SendInput(1, &buffer, sizeof(INPUT));
    WORD vkey = 0x46; // see link below
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = vkey;
    input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
    SendInput(1, &input, sizeof(INPUT));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
    return;  
};

