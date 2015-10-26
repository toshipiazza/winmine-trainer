#include <Windows.h>
#include "common_globals.h"

#define UNUSED(c) (c) = (c)

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    UNUSED(hinstDLL);
    UNUSED(lpvReserved);

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            // TODO: get entire layout and print it out too!
            GameOver(1); // 1 for win
            break;
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default:
            break;
    }
    return TRUE;
}