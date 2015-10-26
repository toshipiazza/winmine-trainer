#ifndef COMMON_GLOBALS_H
#define COMMON_GLOBALS_H

/* Type: const char tiles_on_screen[0x20][0x10]
 * Format: first/last chars on row = 0x10 (filler)
 */
char **tiles_on_screen = reinterpret_cast<char **>(0x01005360);
enum class visible_tiles_t {
    DEPRESSED = 0x40, NORMAL = 0x0F, BOMB = 0xCC,
    ONE = 0x41, TWO = 0x42, THREE = 0x42, FOUR = 0x44
};

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