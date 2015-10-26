#ifndef COMMON_GLOBALS_H
#define COMMON_GLOBALS_H

#include <map>

// case 0, get tile layout

/* Type: const char tiles_on_screen[0x20][0x10]
 * Format: first/last chars on row = 0x10 (filler)
 */
unsigned char *tiles_on_screen = reinterpret_cast<unsigned char *>(0x01005360);
std::map<unsigned int, char> visible_tile_translator = {
    { 0x40, '0' }, { 0x41, '1' }, { 0x42, '2' }, { 0x43, '3' }, { 0x44, '4' },
    { 0x0F, '/' }, { 138,  'x' }, { 143,  '*' }, { 204,  'X' }
};

unsigned int *xBoxMac = reinterpret_cast<unsigned int *>(0x01005334);
unsigned int *yBoxMac = reinterpret_cast<unsigned int *>(0x01005338);

// case 1, make mines visible
void (__stdcall *ShowBombs)(int) =
    reinterpret_cast<void(__stdcall *)(int)>(0x01002F80);

// case 3, freeze timer
void(__stdcall *PauseGame)(void) =
    reinterpret_cast<void(__stdcall *)(void)>(0x0100341C);

// case 4, auto win
int *cBombLeft =
    reinterpret_cast<int *>(0x01005194);
void (__stdcall *GameOver)(int) = // takes 1 or 0
    reinterpret_cast<void(__stdcall *)(int)>(0x0100347C);

#endif
