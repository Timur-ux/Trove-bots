#include <iostream>
#include "Bypass.cpp"
#include "ReloadBuy.cpp"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

double sum(vector<double> v)
{
    double result = 0;
    for(double el: v)
    {
        result += el;
    }
    return result;
}

int main()
{
    Sleep(5000);
    Bypass bypass;
    bypass.Attach(5480);
    vector<uintptr_t> offsets = {0x01cedc50, 0x3c, 0x0, 0x4};
    uintptr_t Offset_result;
    int result, count;
    char c;
    ofstream log("Credit Pouch_log.txt");
    // log << "Name" << ',' << "sumCost" << ',' << "UnitCost" << endl;
    string name = "Credit Pouch";
    vector<double> cache;
    for(int i = 0;; i++)
    {
        reload();
        Sleep(1000);
        Offset_result = bypass.ReadChain(offsets);
        if(i <= 3)
        {
            cout << hex <<Offset_result << dec << ',' << result << ',' << count << ',' << (double)result/count << endl;
        }
        bypass.Read(Offset_result, &result, sizeof(int));
        bypass.Read(Offset_result-4, &count, sizeof(int));
        if(i%5==0)
        {
            log << name << ',' << result << ',' << (double)result/count << endl;
        }
        if(1000000 >= (double)result/count)
        {
            cout << "Buying " << count << ' ' << name << " for " << result << " flux" << endl;
            log << "Buying " << count << ' ' << name << " for " << result << " flux" << endl;
            Sleep(500);
            buy();
        }
        cache.push_back((double)result/count);
        if(cache.size()>100)
        {
            cache.erase(cache.begin());
        }
        Sleep(3000);
    }
    return 0;
}