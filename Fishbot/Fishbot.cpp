#include <iostream>
#include "Bypass.cpp"
#include "Keyboard.cpp"
#include <vector>
// #include <fstream>
#include <string>
using namespace std;

int main()
{
    Bypass bypass;
    uintptr_t pid = bypass.GetProcessIDByName("Trove.exe");

    if(!bypass.Attach(pid))
    {
        cout << "Attach Error" << endl;
    }
    uintptr_t base = (uintptr_t)bypass.GetModuleBase();
    vector<uintptr_t> offsets = {base+0x0100CC14, 0x68, 0xe4, 0x3c4};
    uintptr_t Offset_result;
    int result;
    cout << "Press ENTER button to start" << endl;
    getchar();
    Offset_result = bypass.ReadChain(offsets);
    cout << "Start fishing across 5 second, turn game window to front" << endl;
    Sleep(5000);
    Keyboard keyboard;
    for(;;)
    {
        keyboard.click();
        Sleep(3000);
        bypass.Read(Offset_result, &result, sizeof(int));
        while(result != 1)
        {
            Sleep(1000);
            cout << result << endl;
            bypass.Read(Offset_result, &result, sizeof(int));
        }
        Sleep(500);
        keyboard.click();
        Sleep(3000);
    }
    return 0;
}