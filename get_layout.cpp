#include <Windows.h>
#include "common_globals.h"
#include <sstream>
#include <iomanip>

void
extract_tiles_layout(std::stringstream &);

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    #define UNUSED(c) (c) = (c)
    UNUSED(hinstDLL);
    UNUSED(lpvReserved);
    std::stringstream ss;

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            extract_tiles_layout(ss);
            MessageBoxA(nullptr, ss.str().c_str(), "Layout of tiles!", MB_OK);
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
extract_tiles_layout(std::stringstream &ss)
{
    ss << "LEGEND:" << std::endl
       << "empty tile = 0" << std::endl
       << "unpressed tile = /" << std::endl
       << "exploded bomb = x" << std::endl
       << "red bomb (set off) = X" << std::endl
       << "hidden bomb = *" << std::endl << std::endl;
    for (unsigned int i = 0; i < *xBoxMac; ++i) {
        for (unsigned int j = 1; j <= *yBoxMac; ++j) {
            switch (*(tiles_on_screen + j + 0x20 * i)) {
            case DEPRESSED: ss << "0"; break;
            case ONE: ss << "1"; break;
            case TWO: ss << "2"; break;
            case THREE: ss << "3"; break;
            case FOUR: ss << "4"; break;
            case NORMAL: ss << "/"; break;
            case BOMB: ss << "x"; break;
            case RED_BOMB: ss << "X"; break;
            case HIDDEN_BOMB: ss << "*"; break;
            }
        }
        ss << std::endl;
    }
}
