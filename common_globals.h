#ifndef COMMON_GLOBALS_H
#define COMMON_GLOBALS_H

#include <map>

std::map<unsigned int, char> visible_tile_translator = {
    { 0x40, '0' }, { 0x41, '1' }, { 0x42, '2' }, { 0x43, '3' }, { 0x44, '4' },
    { 0x0F, ' ' }, { 138, 'x' }, { 143, '*' }, { 204, 'X' }
};

/* Type: const char tiles_on_screen[0x20][0x10]
 * Format: first/last chars on row = 0x10 (filler)
 */
unsigned char *tiles_on_screen = (unsigned char *) 0x01005360;
unsigned int *xBoxMac = (unsigned int *) 0x01005334;
unsigned int *yBoxMac = (unsigned int *) 0x01005338;

void(__stdcall *ShowBombs)(int) = (void(_stdcall *)(int)) 0x01002F80;
void(__stdcall *PauseGame)(void) = (void(_stdcall *)(void)) 0x0100341C;
void(__stdcall *GameOver)(int) = (void(__stdcall *)(int)) 0x0100347C; // takes 1 or 0

#endif
