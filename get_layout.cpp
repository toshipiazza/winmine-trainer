#include <Windows.h>
#include <fstream>

#include "common_globals.h"

void
ExtractTilesLayout(std::ofstream &);

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
#define UNUSED(c) (c) = (c)
    UNUSED(hinstDLL);
    UNUSED(lpvReserved);
#undef UNUSED
    std::ofstream out("layout.txt");

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            ExtractTilesLayout(out);
            out.close();
            system("notepad layout.txt");
            break;
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default:
            break;
    }
    return TRUE;
}

void
ExtractTilesLayout(std::ofstream &ss)
{
    // solve board, works even if there is garbage on the board
    for (unsigned int i = 0; i < *yBoxMac; ++i) {
        for (unsigned int j = 1; j <= *xBoxMac; ++j) {
            if (GetTile(i, j) & IS_BOMB) ss << 'X';
            else ss << (char) ('0' + CountBombs(j, i+1));
        }
        ss << std::endl;
    }
}