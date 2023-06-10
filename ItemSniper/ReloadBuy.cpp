#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0500

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include <vector>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
void MouseSetup(INPUT *buffer)
{
    buffer->type = INPUT_MOUSE;
    buffer->mi.dx = (0 * (0xFFFF / SCREEN_WIDTH));
    buffer->mi.dy = (0 * (0xFFFF / SCREEN_HEIGHT));
    buffer->mi.mouseData = 0;
    buffer->mi.dwFlags = MOUSEEVENTF_ABSOLUTE;
    buffer->mi.time = 0;
    buffer->mi.dwExtraInfo = 0;
};


void MouseMoveAbsolute(INPUT *buffer, int x, int y)
{
    buffer->mi.dx = (x * (0xFFFF / SCREEN_WIDTH));
    buffer->mi.dy = (y * (0xFFFF / SCREEN_HEIGHT));
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE);

    SendInput(1, buffer, sizeof(INPUT));
};


void MouseClick(INPUT *buffer)
{
    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
    SendInput(1, buffer, sizeof(INPUT));

    Sleep(10);

    buffer->mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
    SendInput(1, buffer, sizeof(INPUT));
};

std::vector<std::vector<int>> pos = {{339, 728}, {607, 335}, {598, 515}};

void reload()
{
    int X = pos[0][0];
    int Y = pos[0][1];
    INPUT buffer;

    MouseSetup(&buffer);

    MouseMoveAbsolute(&buffer, X, Y);
    Sleep(100);
    MouseClick(&buffer);
    return;
}

void buy()
{
    int x1 = pos[1][0]; int y1 = pos[1][1];
    int x2 = pos[2][0]; int y2 = pos[2][1];
    INPUT buffer;

    MouseSetup(&buffer);

    MouseMoveAbsolute(&buffer, x1, y1);
    MouseClick(&buffer);
    Sleep(500);
    MouseMoveAbsolute(&buffer, x2, y2);
    MouseClick(&buffer);
    return;
}


void Chek()
{
    Sleep(3000);
    INPUT buffer;

    MouseSetup(&buffer);

    MouseMoveAbsolute(&buffer, pos[0][0], pos[0][1]);
    Sleep(3000);
    MouseMoveAbsolute(&buffer, pos[1][0], pos[1][1]);
    MouseClick(&buffer);
    Sleep(500);
    Sleep(3000);
    MouseMoveAbsolute(&buffer, pos[2][0], pos[2][1]);
    return;
}

// int main()
// {
//     Chek();
//     return 0;
// }