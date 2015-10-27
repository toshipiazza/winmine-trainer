#include <Windows.h>
#include "common_globals.h"

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
#define UNUSED(c) (c) = (c)
    UNUSED(hinstDLL);
    UNUSED(lpvReserved);
#undef UNUSED

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
#define GET_BOMB(x, y) ((GetTile((x), (y)) & IS_BOMB) != 0)
            for (unsigned int i = 0; i < *yBoxMac; ++i) {
                for (unsigned int j = 1; j <= *xBoxMac; ++j) {
                    // step on it if it's not a bomb
                }
            }
#undef GET_BOMB
            // GameOver(1); // 1 for win
            break;
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default:
            break;
    }
    return TRUE;
}