#include <windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <Psapi.h>
class Bypass
{
    public:
    Bypass();
    ~Bypass();
    bool Attach(DWORD pid);
    bool Read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead);
    bool Write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten);
    uintptr_t ReadChain(std::vector<uintptr_t> offsets);
    uintptr_t GetProcessIDByName(const char* szProcessName);
    HMODULE GetModuleBase();
    private:
    HANDLE m_hProcess = NULL;
};

Bypass::Bypass()
{

};

Bypass::~Bypass()
{
    std::cout << "closing handle" << std::endl;
    if(m_hProcess != NULL) CloseHandle(m_hProcess);
};

bool Bypass::Attach(DWORD pid)
{
    m_hProcess = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION, TRUE, pid);
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
}
uintptr_t Bypass::GetProcessIDByName(const char* szProcessName)
{
    uintptr_t processID = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe32{};
        pe32.dwSize = sizeof(pe32);

        if (Process32First(hSnap, &pe32))
        {
            do
            {
                if (!_strcmpi(szProcessName, (const char*)pe32.szExeFile))
                {
                    processID = pe32.th32ProcessID;
                    break;
                }

            } while (Process32Next(hSnap, &pe32));
        }
    }

    if (hSnap)
        CloseHandle(hSnap);
    return processID;
}

HMODULE Bypass::GetModuleBase()
{
    HMODULE hMods[1024];
    // HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    // Print the process identifier.

    // printf( "\nProcess ID: %u\n", processID );

    // Get a handle to the process.

    // hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
    //                         PROCESS_VM_READ,
    //                         FALSE, processID );
    // if (NULL == hProcess)
    //     return 1;

   // Get a list of all the modules in this process.
    
    if( EnumProcessModules(this->m_hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
        {
            TCHAR szModName[MAX_PATH];

            // Get the full path to the module's file.

            if ( GetModuleFileNameEx( this->m_hProcess, hMods[i], szModName,
                                      sizeof(szModName) / sizeof(TCHAR)))
            {
                // Print the module name and handle value.
                return hMods[i];
                std::cout << szModName << ' ' << hMods[i] << std::endl;
                // printf( TEXT("\t%s (0x%08X)\n"), szModName, hMods[i] );
            }
        }
    }
    else
    {
        std::cout << "OPEN ERROR, lError = " << GetLastError() << std::endl;
    }
    
    // Release the handle to the process
}