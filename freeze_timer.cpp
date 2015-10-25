#include <Windows.h>

#define UNUSED(c) (c) = (c)

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    UNUSED(hinstDLL);
    UNUSED(lpvReserved);

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            MessageBoxA(NULL, "hello", "world", MB_OK);
            break;
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default:
            break;
    }
    return TRUE;
}