#include <Windows.h>
#include "common_globals.h"

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    #define UNUSED(c) (c) = (c)
    UNUSED(hinstDLL);
    UNUSED(lpvReserved);

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            ShowBombs(0xa); // 0xa loads the bitmap for the bomb
                            // simply looking at the usage for ShowBombs
                            // in the binary tells us how to use it
            break;
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default:
            break;
    }
    return TRUE;
}