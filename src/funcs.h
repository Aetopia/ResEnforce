#pragma once

#include "helpers.h"
#include "ini.h"
#include <unistd.h>
#include <winuser.h>
#include <libgen.h>
#include <stdio.h>

struct WindowInfo
{
    char *title;
    char *exe;
    DWORD pid;
};

struct WindowInfo GetForegroundWindowInfo();

void OptsExist();

// Profiles
BOOL ProfCheck(char *app);
char *ProfLoad(char *app);

// Resolution Handler
void ResReset();
void ResApply();