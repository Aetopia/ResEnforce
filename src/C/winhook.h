#pragma once

#include <windows.h>
#include <psapi.h>
#include <winuser.h>
#include <libgen.h>

struct Window
{
    char *title;
    char *exe;
};

struct Window GetForegroundWindowInfo();