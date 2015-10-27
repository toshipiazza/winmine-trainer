#ifndef COMMON_GLOBALS_H
#define COMMON_GLOBALS_H

/* see writeup for explanation
 * we stepped into the debugger and manipulated these values to find
 * the values on the tiles through an & 0x1F
 */
char visible_tile_translator[] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7', '8',
    'Q', 'x', '/', 'X', 'q', 'F', '-'
};
unsigned int BOMB = 143;

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
