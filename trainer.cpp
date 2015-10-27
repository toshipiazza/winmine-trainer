#include <Windows.h>
#include <iostream>
#include "inject.h"

#ifdef __MINGW32__
#define PRE "lib"
#else
#define PRE
#endif

const char *jtOpt[] = {
    PRE "get_layout.dll",
    PRE "mines_visible.dll",
    PRE "freeze_timer.dll",
    PRE "disable_mines.dll",
    PRE "auto_win.dll" };

HANDLE
CreateWinMineProcess();

int
main(void)
{
    std::cout << "Please wait... initializing winmine.exe" << std::endl;

    unsigned int nOpt;
    HANDLE hWinMine = CreateWinMineProcess();
    HMODULE hAttackerModule = nullptr;
    if (!hWinMine) {
        std::cerr << "ERROR: could not initialize winmine.exe" << std::endl;
        system("pause");
        return 1;
    }

    while (true) {
        std::cout << "Welcome to the minesweeper trainer!" << std::endl
                  << "0. Get the layout of the tiles" << std::endl
                  << "1. Make the mines visible" << std::endl
                  << "2. Freeze the timer" << std::endl
                  << "3. Disable mines" << std::endl
                  << "4. Auto win?" << std::endl
                  << "5. Quit" << std::endl
                  << "Please select an option ===> " << std::flush;
        std::cin >> nOpt;

        if (nOpt >= 0 && nOpt < 5) {
            // all the work is done in each's respective DllMain
            hAttackerModule = DllInject(jtOpt[nOpt], hWinMine);
            system("pause");
            if (hAttackerModule) DllFree(hAttackerModule, hWinMine);
            hAttackerModule = nullptr;
        } else if (nOpt == 5) {
            std::cout << "Bye! <3 ~~" << std::endl;
            break;
        }
    }

    // bad voodoo...
    TerminateProcess(hWinMine, 0);
    CloseHandle(hWinMine);
    return 0;
}

HANDLE
CreateWinMineProcess()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // create winmine.exe
    CreateProcess("winmine.exe", nullptr, nullptr, nullptr,
                  FALSE, 0, nullptr, nullptr,
                  &si, &pi);
    CloseHandle(pi.hThread);
    return pi.hProcess;
}
