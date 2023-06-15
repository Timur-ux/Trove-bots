#define WIN32_LEAN_AND_MEAN

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

#ifndef _INCLUDE_WINDOWS_H_
#define _INCLUDE_WINDOWS_H_
#include <Windows.h>
#endif

#include <vector>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class Mouse
{
    public:
        INPUT buffer;
        Mouse();
        void MouseMoveAbsolute(int x, int y);
        void MouseClick();
};

Mouse::Mouse()
{
    this->buffer.type = INPUT_MOUSE;
    this->buffer.mi.dx = (0 * (0xFFFF / SCREEN_WIDTH));
    this->buffer.mi.dy = (0 * (0xFFFF / SCREEN_HEIGHT));
    this->buffer.mi.mouseData = 0;
    this->buffer.mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
    this->buffer.mi.time = 0;
    this->buffer.mi.dwExtraInfo = 0;
}

void Mouse::MouseMoveAbsolute(int x, int y)
{
    this->buffer.mi.dx = (x * (0xFFFF / SCREEN_WIDTH));
    this->buffer.mi.dy = (y * (0xFFFF / SCREEN_HEIGHT));
    this->buffer.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);

    SendInput(1, &(this->buffer), sizeof(INPUT));
};


void Mouse::MouseClick()
{
    this->buffer.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
    SendInput(1, &(this->buffer), sizeof(INPUT));

    Sleep(10);

    this->buffer.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
    SendInput(1, &(this->buffer), sizeof(INPUT));
};

Mouse mouse;
// std::vector<std::vector<int>> pos = {{424, 685}, {687, 298}, {676, 471}};
std::vector<std::vector<int>> pos = {{ 610, 795 },{ 878, 403 },{ 865, 561 }};
void reload()
{
    int x = pos[0][0];
    int y = pos[0][1];
    mouse.MouseMoveAbsolute(x, y);
    Sleep(100);
    mouse.MouseClick();
    return;
}

void buy()
{
    int x1 = pos[1][0]; int y1 = pos[1][1];
    int x2 = pos[2][0]; int y2 = pos[2][1];

    mouse.MouseMoveAbsolute(x1, y1);
    mouse.MouseClick();
    Sleep(500);
    mouse.MouseMoveAbsolute(x2, y2);
    mouse.MouseClick();
    return;
}


void Chek()
{
    Sleep(3000);
    mouse.MouseMoveAbsolute(pos[0][0], pos[0][1]);
    Sleep(3000);
    mouse.MouseMoveAbsolute(pos[1][0], pos[1][1]);
    mouse.MouseClick();
    Sleep(3500);
    mouse.MouseMoveAbsolute(pos[2][0], pos[2][1]);
    return;
}

// int main()
// {
//     Chek();
//     return 0;
// }