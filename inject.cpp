#include "inject.h"
#include <iostream>

#include <Psapi.h>
#pragma comment(lib, "psapi.lib")

HMODULE
DllInject(LPCSTR szInjectDll, HANDLE hVictim)
{
    HANDLE hAttacker;
    LPVOID pInjectDll = NULL;
    FARPROC pLoadLibrary = NULL;

    // needed to return the created hModule...
    HMODULE hVictimModules[200];
    DWORD nVictimModules;
    CHAR szVictimModuleName[MAX_PATH];

    // allocate and write name of dll into victim
    pInjectDll = VirtualAllocEx(hVictim, NULL,
                                strlen(szInjectDll) + 1,
                                MEM_RESERVE | MEM_COMMIT,
                                PAGE_READWRITE);
    WriteProcessMemory(hVictim, pInjectDll, szInjectDll,
                       strlen(szInjectDll) + 1, NULL);

    // resolve address or LoadLibraryA within victim
    // works because probably target process has same
    // dll loaded in same place...
    pLoadLibrary = (FARPROC)
            GetProcAddress(GetModuleHandle("Kernel32.dll"),
                           "LoadLibraryA");
    // victimize process
    hAttacker = CreateRemoteThread(hVictim, NULL, 0,
                                   (LPTHREAD_START_ROUTINE)
                                           pLoadLibrary,
                                   pInjectDll, 0, NULL);
    if (hAttacker == NULL) {
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
    return NULL;
}

void
DllFree(HMODULE szInjectDll, HANDLE hVictim)
{
    HANDLE hAttacker;
    FARPROC pFreeLibrary = NULL;

    // same as above... Kernel32.dll placement and ASLR ftw
    pFreeLibrary = (FARPROC)
            GetProcAddress(GetModuleHandle("Kernel32.dll"),
                           "FreeLibrary");
    hAttacker = CreateRemoteThread(hVictim, NULL, 0,
                                   (LPTHREAD_START_ROUTINE)
                                           pFreeLibrary,
                                   szInjectDll, 0, NULL);
    if (hAttacker == NULL) {
        std::cerr << "ERROR: Remote thread could not be created" << std::endl;
    } else {
        WaitForSingleObject(hAttacker, INFINITE);
        CloseHandle(hAttacker);
    }
}