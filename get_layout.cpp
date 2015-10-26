#include <Windows.h>
#include "common_globals.h"
#include <sstream>
#include <fstream>

void
extract_tiles_layout(std::ofstream &);

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    #define UNUSED(c) (c) = (c)
    UNUSED(hinstDLL);
    UNUSED(lpvReserved);
    std::ofstream out("layout.txt");

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            extract_tiles_layout(out);
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
extract_tiles_layout(std::ofstream &ss)
{
    ss << "LEGEND:" << std::endl
       << "empty tile = 0" << std::endl
       << "unpressed tile = /" << std::endl
       << "exploded bomb = x" << std::endl
       << "red bomb (set off) = X" << std::endl
       << "hidden bomb = *" << std::endl << std::endl;
    for (unsigned int i = 0; i < *xBoxMac; ++i) {
        for (unsigned int j = 1; j <= *yBoxMac; ++j) {
            ss << visible_tile_translator[
                    *(tiles_on_screen + j + 0x20 * i)
                ];
        }
        ss << std::endl;
    }
}
