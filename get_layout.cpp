#include <Windows.h>

#define UNUSED(c) (c) = (c)
#include <sstream>

void
extract_tiles_layout(std::stringstream &);

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
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
    ss << "Method not implemented" << std::endl;
}