#include "inject.h"
#include <iostream>

#include <Psapi.h>
#pragma comment(lib, "psapi.lib")

HMODULE
DllInject(LPCSTR szInjectDll, HANDLE hVictim)
{
    HANDLE hAttacker;
    LPVOID pInjectDll = nullptr;
    LPTHREAD_START_ROUTINE pLoadLibrary = nullptr;

    // needed to return the created hModule...
    HMODULE hVictimModules[200];
    DWORD nVictimModules;
    CHAR szVictimModuleName[MAX_PATH];

    // allocate and write name of dll into victim
    pInjectDll = VirtualAllocEx(hVictim, nullptr,
                                strlen(szInjectDll) + 1,
                                MEM_RESERVE | MEM_COMMIT,
                                PAGE_READWRITE);
    WriteProcessMemory(hVictim, pInjectDll, szInjectDll,
                       strlen(szInjectDll) + 1, nullptr);

    // resolve address or LoadLibraryA within victim
    // works because probably target process has same
    // dll loaded in same place...
    pLoadLibrary = reinterpret_cast<LPTHREAD_START_ROUTINE>(
            GetProcAddress(GetModuleHandle("Kernel32.dll"),
                           "LoadLibraryA"));
    // victimize process
    hAttacker = CreateRemoteThread(hVictim, nullptr, 0, pLoadLibrary,
                                   pInjectDll, 0, nullptr);
    if (hAttacker == nullptr) {
        std::cerr << "ERROR: Remote thread could not be created" << std::endl;
    } else {
        WaitForSingleObject(hAttacker, INFINITE);
        CloseHandle(hAttacker);
    }
    // VirtualFreeEx(hVictim, pInjectDll, strlen(szInjectDll), MEM_DECOMMIT);
    VirtualFreeEx(hVictim, pInjectDll, 0, MEM_RELEASE);

    // find the hmodule of the library we just loaded
    EnumProcessModules(hVictim, hVictimModules, 200, &nVictimModules);
    for (unsigned int i = 0; i < nVictimModules; ++i) {
        GetModuleFileNameEx(hVictim, hVictimModules[i],
                            szVictimModuleName, MAX_PATH);
        if (strstr(szVictimModuleName, szInjectDll))
            return hVictimModules[i];
    }
    // if this happened, we didn't find the module
    // which is bad...
    return nullptr;
}

void
DllFree(HMODULE szInjectDll, HANDLE hVictim)
{
    HANDLE hAttacker;
    LPTHREAD_START_ROUTINE pFreeLibrary = nullptr;

    // same as above... Kernel32.dll placement and ASLR ftw
    pFreeLibrary = reinterpret_cast<LPTHREAD_START_ROUTINE>(
            GetProcAddress(GetModuleHandle("Kernel32.dll"),
                           "FreeLibrary"));
    hAttacker = CreateRemoteThread(hVictim, nullptr, 0, pFreeLibrary,
                                   szInjectDll, 0, nullptr);
    if (hAttacker == nullptr) {
        std::cerr << "ERROR: Remote thread could not be created" << std::endl;
    } else {
        WaitForSingleObject(hAttacker, INFINITE);
        CloseHandle(hAttacker);
    }
}