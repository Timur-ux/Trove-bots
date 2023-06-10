#include <Windows.h>
#include <iostream>
#include <vector>
class Bypass
{
    public:
    Bypass();
    ~Bypass();
    bool Attach(DWORD pid);
    bool Read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead);
    bool Write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten);
    uintptr_t ReadChain(std::vector<uintptr_t> offsets);

    private:
    HANDLE m_hProcess = NULL;
};

Bypass::Bypass()
{

};

Bypass::~Bypass()
{
    if(m_hProcess != NULL) CloseHandle(m_hProcess);
};

bool Bypass::Attach(DWORD pid)
{
    m_hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_VM_OPERATION, FALSE, pid);
    if(m_hProcess != NULL) return true; return true;
};

bool Bypass::Read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead = NULL)
{
    if(ReadProcessMemory(m_hProcess, (LPCVOID)lpBaseAddress, (LPVOID)lpBuffer, nSize, lpNumberOfBytesRead)) return true; return false;
};

bool Bypass::Write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten = NULL)
{
    if(WriteProcessMemory(m_hProcess, (LPVOID)lpBaseAddress, (LPCVOID)lpBuffer, nSize, lpNumberOfBytesWritten)) return true; return false;
}
uintptr_t Bypass::ReadChain(std::vector<uintptr_t> offsets)
{
    uintptr_t lpResult = offsets[0];
    for(int i = 1; i < offsets.size(); i++)
    {
        this->Read(lpResult, &lpResult, sizeof(uintptr_t));
        lpResult += offsets[i];
    }
    return lpResult;
};