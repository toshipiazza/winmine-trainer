#include <Windows.h>
#include "common_globals.h"
#include <fstream>
#include <iomanip>

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

unsigned int
get_tile(unsigned int i, unsigned int j)
{
    return *(tiles_on_screen + j + 0x20 * i);
}

// if there was a number, return it
char
get_number(unsigned int i, unsigned int j)
{
    char out = '0';
    for (int _i = i - 1; _i < (int)i + 2; ++_i) {
        for (int _j = j - 1; _j < (int)j + 2; ++_j) {
            // make sure we're not out of bounds
            if (!(_i == -1 || _j == 0)
                && !(_i == *yBoxMac || _j == *xBoxMac + 1)
                && !(_i == i && _j == j)) {
                out += (get_tile(_i, _j) & IS_BOMB) != 0;
            }
        }
    }
    return out;
}

void
extract_tiles_layout(std::ofstream &ss)
{
    // solve board, works even if there is garbage on the board
    for (unsigned int i = 0; i < *yBoxMac; ++i) {
        for (unsigned int j = 1; j <= *xBoxMac; ++j) {
            if (get_tile(i, j) & IS_BOMB) ss << 'X';
            else ss << get_number(i, j);
        }
        ss << std::endl;
    }
}