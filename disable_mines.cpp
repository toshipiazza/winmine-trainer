#include <Windows.h>

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
#define UNUSED(c) (c) = (c)
    UNUSED(hinstDLL);
    UNUSED(lpvReserved);
#undef UNUSED

    LPCSTR lpNops = "\x90\x90\xeb\x1b";
    LPVOID lpCall2GameOver = (void *) 0x01003591;
    DWORD flOldProtect;

    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            if (VirtualProtect(lpCall2GameOver, strlen(lpNops),
                               PAGE_EXECUTE_READWRITE, &flOldProtect)) {
                MessageBoxA(nullptr, "Patched!", "malware", MB_OK);
                // we patch some bytes which prevents
                // a mine from triggering game over
                memcpy(lpCall2GameOver, lpNops, strlen(lpNops));
                VirtualProtect(lpCall2GameOver, strlen(lpNops),
                               flOldProtect, &flOldProtect);
            } else {
                MessageBoxA(nullptr, "could not virtual protect!", "malware", MB_OK);
            }
            break;
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        default:
            break;
    }
    return TRUE;
}