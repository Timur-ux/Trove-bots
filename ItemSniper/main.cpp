#include <iostream>
#include "Bypass.cpp"
#include "ReloadBuy.cpp"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char * argv[])
{
    Bypass bypass;
    uintptr_t pid = bypass.GetProcessIDByName("Trove.exe");

    if(!bypass.Attach(pid))
    {
        cout << "Attach Error" << endl;
    }
    uintptr_t base = (uintptr_t)bypass.GetModuleBase();
    vector<uintptr_t> offsets = {base+0x0103B124, 0xb8, 0xc, 0x14, 0x140, 0x0, 0x4};
    uintptr_t Offset_result;
    int result, count;
    string name = argv[2];
    int bias = atoi(argv[1]);
    cout << "Press ENTER button to chek connection bot to game" << endl;
    getchar();
    Offset_result = bypass.ReadChain(offsets);
    bypass.Read(Offset_result, &result, sizeof(int));
    bypass.Read(Offset_result-4, &count, sizeof(int));
    cout << name << " AllCost = " << result << ", count = " << count << endl;
    cout << "If Allcost equal first item in market and count equal first item count - allright," << endl;
    cout << "Bot connect correctly? Press Y if yes, any other button if not" << endl; 
    char c = getchar();
    if(c != 'y' && c != 'Y')
    {
        return 0;
    }
    cout << "Start sniping items, turn game window to front" << endl;
    Sleep(5000);

    for(int i = 0;; i++)
    {
        reload();
        Sleep(1000);
        Offset_result = bypass.ReadChain(offsets);
        bypass.Read(Offset_result, &result, sizeof(int));
        bypass.Read(Offset_result-4, &count, sizeof(int));
        if(i <= 3)
        {
            cout << name << " cost = " << result << ",  count = " << count << ", Unit price = " << (double)result/count << endl;
        }
        if(bias >= (double)result/count)
        {
            cout << "Trying to Buy " << count << ' ' << name << " for " << result << " flux" << endl;
            Sleep(500);
            buy();
        }
        Sleep(4000);
    }
    return 0;
}
