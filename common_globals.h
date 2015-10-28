#ifndef COMMON_GLOBALS_H
#define COMMON_GLOBALS_H

// flags
const unsigned int IS_BOMB = 0x80;
const unsigned int NUMERIC = 0x40;

// masks
const unsigned int VISIBLE = 0x1F;
const unsigned int FLAGGED = 0xFE;
const unsigned int GUESSED = 0xFD;

/* Type: const char tiles_on_screen[0x20][0x10]
 * Format: first/last chars on row = 0x10 (filler)
 */
const unsigned char *tiles_on_screen = (unsigned char *) 0x01005360;
const unsigned int *xBoxMac = (unsigned int *) 0x01005334;
const unsigned int *yBoxMac = (unsigned int *) 0x01005338;

const void(__stdcall *ShowBombs)(int) = (const void(__stdcall *)(int)) 0x01002F80;
const void(__stdcall *PauseGame)(void) = (const void(__stdcall *)(void)) 0x0100341C;
const void(__stdcall *StepSquare)(int,int) = (const void(__stdcall *)(int,int)) 0x01003512;
// const void(__stdcall *GameOver)(int) = (const void(__stdcall *)(int)) 0x0100347C;

inline unsigned int
GetTile(unsigned int i, unsigned int j)
{
    return *(tiles_on_screen + j + 0x20 * i);
}

#endif