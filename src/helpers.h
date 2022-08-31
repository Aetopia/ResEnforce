#pragma once

#include <windows.h>
#include <psapi.h>

int AutoDelay();

char *GetTitle(HWND hwnd);
char *GetExe(DWORD pid);
DWORD GetPID(HWND hwnd);