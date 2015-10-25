#ifndef INJECT_H
#define INJECT_H

#include <Windows.h>

HMODULE
DllInject(LPCSTR szInjectDll, HANDLE hVictim);

void
DllFree(HMODULE szInjectDll, HANDLE hVictim);

#endif