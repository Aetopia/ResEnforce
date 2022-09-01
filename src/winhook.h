#pragma once

#include <windows.h>
#include <psapi.h>
#include <winuser.h>
#include <libgen.h>

struct WindowInfo
{
    char *title;
    char *exe;
};

DWORD GetWindowPID(HWND hwnd);
char *GetWindowTitle(HWND hwnd);
char *GetWindowExe(DWORD pid);
struct WindowInfo GetForegroundWindowInfo();
